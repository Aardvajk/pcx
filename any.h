#ifndef PCX_ANY_H
#define PCX_ANY_H

#include <type_traits>
#include <typeinfo>
#include <cstring>

#include <iostream>

namespace pcx
{

class any
{
public:
    any() : ops(nullptr) { }
    template<typename T> any(const T &v){ construct(v); }
    any(const any &v) : ops(v.ops) { if(ops) ops->copy(v.store, store); }
    any(any &&v) : ops(v.ops) { if(ops) ops->move(v.store, store); }
    ~any(){ if(ops) ops->destroy(store); }

    any &operator=(const any &v){ any(v).swap(*this); return *this; }
    any &operator=(any &&v){ any(std::move(v)).swap(*this); return *this; }

    template<typename T> any &operator=(const T &v){ any(v).swap(*this); return *this; }

    void swap(any &v){ std::swap(store, v.store); std::swap(ops, v.ops); }

    template<typename T> T to() const { return *reinterpret_cast<const T*>(ops->ptr(store)); }
    template<typename T> T value() const { return type() == typeid(T) ? to<T>() : T(); }

    bool has_value() const { return static_cast<bool>(ops); }
    operator bool() const { return has_value(); }

    const std::type_info &type() const { return ops ? ops->type() : typeid(void); }

private:
    operator int() const = delete;

    struct storage
    {
        union
        {
            std::aligned_storage<sizeof(void*)>::type stack;
            void *heap;
        };
    };

    template<typename T> struct stackable : std::integral_constant<bool, sizeof(T) <= sizeof(storage)> { };

    struct operations
    {
        void(*copy)(const storage&, storage&);
        void(*move)(storage&, storage&);
        void(*destroy)(storage&);
        const void*(*ptr)(const storage&);
        const std::type_info&(*type)();
    };

    template<typename T> struct operations_stack
    {
        static void copy(const storage &src, storage &dest){ new(&dest.stack) T(*reinterpret_cast<const T*>(&src.stack)); }
        static void move(storage &src, storage &dest){ new(&dest.stack) T(*reinterpret_cast<const T*>(&src.stack)); }
        static void destroy(storage &store){ reinterpret_cast<T*>(&store.stack)->~T(); }
        static const void *ptr(const storage &store){ return &store.stack; }
        static const std::type_info &type(){ return typeid(T); }
    };

    template<typename T> struct operations_heap
    {
        static void copy(const storage &src, storage &dest){ dest.heap = new T(*reinterpret_cast<const T*>(src.heap)); }
        static void move(storage &src, storage &dest){ dest.heap = src.heap; src.heap = nullptr; }
        static void destroy(storage &store){ delete reinterpret_cast<T*>(store.heap); }
        static const void *ptr(const storage &store){ return store.heap; }
        static const std::type_info &type(){ return typeid(T); }
    };

    template<typename T> static operations *get_ops()
    {
        using Type = typename std::conditional<stackable<T>::value, operations_stack<T>, operations_heap<T> >::type;
        static operations o = { Type::copy, Type::move, Type::destroy, Type::ptr, Type::type };

        return &o;
    }

    template<typename T, bool> struct constructor;

    template<typename T> struct constructor<T, true>
    {
        void operator()(const T &v, storage &store){ new(&store.stack) T(v); }
    };

    template<typename T> struct constructor<T, false>
    {
        void operator()(const T &v, storage &store){ store.heap = new T(v); }
    };

    template<typename T> void construct(const T &v)
    {
        constructor<T, stackable<T>::value>()(v, store);
        ops = get_ops<T>();
    }

    storage store;
    operations *ops;
};

}

#endif // PCX_ANY_H
