#ifndef PCX_OPTIONAL_H
#define PCX_OPTIONAL_H

#include <type_traits>
#include <utility>

#include <iostream>

namespace pcx
{

struct nullopt_t
{
    constexpr nullopt_t(int){ }
};

extern const nullopt_t nullopt;

struct in_place_t
{
    constexpr in_place_t(int){ }
};

extern const in_place_t in_place;

template<typename T> class optional
{
public:
    optional() : v(false) { }
    optional(nullopt_t) : v(false) { }
    optional(const T &t) : v(true) { new(&s) T(t); }
    optional(const optional &o) : v(o.v) { if(v) new(&s) T(*o); }
    template<typename... Args> optional(in_place_t, Args&&... args) : v(true) { new(&s) T(std::forward<Args>(args)...); }
    ~optional(){ if(v) reinterpret_cast<T*>(&s)->~T(); }

    optional &operator=(const optional &o){ if(v) reinterpret_cast<T*>(&s)->~T(); v = o.v; if(v) new(&s) T(*o); return *this; }

    bool operator==(const optional &o) const { return v ? o.v && *(reinterpret_cast<const T*>(&s)) == *(reinterpret_cast<const T*>(&o.s)) : !o.v; }
    bool operator!=(const optional &o) const { return !(*this == o); }

    operator bool() const { return v; }
    bool valid() const { return v; }

    T &operator*(){ return *reinterpret_cast<T*>(&s); }
    const T &operator*() const { return *reinterpret_cast<const T*>(&s); }

    T *operator->(){ return reinterpret_cast<T*>(&s); }
    const T *operator->() const { return reinterpret_cast<const T*>(&s); }

private:
    bool v;
    typename std::aligned_storage<sizeof(T)>::type s;
};

}

#endif // PCX_OPTIONAL_H
