#ifndef PCX_OPTIONAL_H
#define PCX_OPTIONAL_H

#include <utility>

namespace pcx
{

struct nullopt_t
{
    constexpr nullopt_t(int){ }
};

extern const nullopt_t nullopt;

template<typename T> class optional
{
public:
    optional() : t(T()), v(false) { }
    optional(T t) : t(std::move(t)), v(true) { }
    optional(nullopt_t) : v(false) { }

    optional &operator=(T c){ t = std::move(c); v = true; return *this; }

    bool operator==(const optional &o) const { return v ? o.v && t == o.t : !o.v; }
    bool operator!=(const optional &o) const { return !(*this == o); }

    operator bool() const { return v; }

    T &operator*(){ return t; }
    const T &operator*() const { return t; }

    T *operator->(){ return &t; }
    const T *operator->() const { return &t; }

private:
    T t;
    bool v;
};

}

#endif // PCX_OPTIONAL_H
