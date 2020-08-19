#ifndef PCX_PTR_VECTOR_H
#define PCX_PTR_VECTOR_H

#include <pcx/non_copyable.h>

#include <vector>

namespace pcx
{

template<typename T, typename D> class basic_ptr_vector
{
public:
    using value_type = T;
    using size_type = typename std::vector<T*>::size_type;

    class iterator
    {
    public:
        bool operator==(const iterator &o) const { return i == o.i; }
        bool operator!=(const iterator &o) const { return i != o.i; }

        iterator operator+(std::ptrdiff_t s) const { return iterator(i + s); }
        iterator operator-(std::ptrdiff_t s) const { return iterator(i - s); }

        iterator &operator++(){ ++i; return *this; }
        iterator operator++(int){ return iterator(i++); }

        iterator &operator--(){ --i; return *this; }
        iterator operator--(int){ return iterator(i--); }

        T &operator*() const { return *(*i); }
        T *operator->() const { return *i; }

    private:
        friend class basic_ptr_vector;

        explicit iterator(typename std::vector<T*>::iterator i) : i(i) { }

        typename std::vector<T*>::iterator i;
    };

    class const_iterator
    {
    public:
        bool operator==(const const_iterator &o) const { return i == o.i; }
        bool operator!=(const const_iterator &o) const { return i != o.i; }

        const_iterator operator+(std::ptrdiff_t s) const { return const_iterator(i + s); }
        const_iterator operator-(std::ptrdiff_t s) const { return const_iterator(i - s); }

        const_iterator &operator++(){ ++i; return *this; }
        const_iterator operator++(int){ return const_iterator(i++); }

        const_iterator &operator--(){ --i; return *this; }
        const_iterator operator--(int){ return const_iterator(i--); }

        const T &operator*() const { return *(*i); }
        const T *operator->() const { return *i; }

    private:
        friend class basic_ptr_vector;

        explicit const_iterator(typename std::vector<T*>::const_iterator i) : i(i) { }

        typename std::vector<T*>::const_iterator i;
    };

    basic_ptr_vector() = default;
    ~basic_ptr_vector(){ for(auto &i: v) D()(i); }

    void push_back(T *t){ v.push_back(t); }
    void pop_back(){ D()(v.back()); v.pop_back(); }
    void clear(){ for(auto &i: v) D()(i); v.clear(); }

    template<typename... Args> void emplace_back(Args&&... args){ v.push_back(new T(std::forward<Args>(args)...)); }

    iterator erase(iterator i){ D()(*(i.i)); return iterator(v.erase(i.i)); }
    iterator erase(iterator a, iterator b){ for(auto i = a; i != b; ++i) D()(*(i.i)); return iterator(v.erase(a.i, b.i)); }

    void replace_ptr(size_type index, T *t){ D()(v[index]); v[index] = t; }
    void replace(T *before, T *after){ for(size_type i = 0; i < size(); ++i) if(ptr(i) == before){ replace_ptr(i, after); return; } }
    void replace_all(T *before, T *after){ for(size_type i = 0; i < size(); ++i) if(ptr(i) == before) replace_ptr(i, after); }

    iterator insert(iterator pos, T *value){ return iterator(v.insert(pos.i, value)); }

    T &operator[](size_type i){ return *(v[i]); }
    const T &operator[](size_type i) const { return *(v[i]); }

    T *ptr(size_type i){ return v[i]; }
    const T *ptr(size_type i) const { return v[i]; }

    iterator begin(){ return iterator(v.begin()); }
    iterator end(){ return iterator(v.end()); }

    const_iterator begin() const { return const_iterator(v.begin()); }
    const_iterator end() const { return const_iterator(v.end()); }

    T &front(){ return *(v.front()); }
    const T &front() const { return *(v.front()); }

    T &back(){ return *(v.back()); }
    const T &back() const { return *(v.back()); }

    T *back_ptr(){ return v.back(); }
    const T *back_ptr() const { return v.back(); }

    size_type size() const { return v.size(); }
    bool empty() const { return v.empty(); }

    void remove_all(T *t){ auto i = v.begin(); while(i != v.end()){ if(*i == t){ D()(*i); i = v.erase(i); } else ++i; } }

    T *release(size_type index){ T *t = v[index]; v[index] = nullptr; return t; }
    T *release_back(){ T *t = v.back(); v.pop_back(); }
    void release_all(T *t){ v.remove_all(t); }

    const std::vector<T*> &raw() const { return v; }

private:
    std::vector<T*> v;
};

template<typename T> struct ptr_vector_deleter
{
    void operator()(T *p) const { delete p; }
};

template<typename T> class ptr_vector : public basic_ptr_vector<T, ptr_vector_deleter<T> >
{
public:
    ptr_vector() = default;

private:
    ptr_vector(const ptr_vector&) = delete;
    void operator=(const ptr_vector&) = delete;
};

template<typename T> struct ptr_view_vector_deleter
{
    void operator()(T*) const { }
};

template<typename T> class ptr_view_vector : public basic_ptr_vector<T, ptr_view_vector_deleter<T> >
{
public:
    ptr_view_vector() = default;
};

}

#endif // PCX_PTR_VECTOR_H
