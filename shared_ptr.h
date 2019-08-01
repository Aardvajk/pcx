#ifndef PCX_SHARED_PTR_H
#define PCX_SHARED_PTR_H

#include <cstdlib>

namespace pcx
{

template<typename T> class shared_ptr
{
public:
    shared_ptr() : r(new rep(nullptr)) { }
    shared_ptr(T *p) : r(new rep(p)) { }
    shared_ptr(const shared_ptr &o) : r(o.r) { ++r->n; }
    ~shared_ptr(){ if(!--r->n) delete r->p; }

    shared_ptr &operator=(const shared_ptr &o){ if(!--r->n) delete r->p; r = o.r; ++r->n; return *this; }

    operator bool() const { return r->p; }

    T *operator->(){ return r->p; }
    const T *operator->() const { return r->p; }

    T &operator*(){ return *r->p; }
    const T &operator*() const { return *r->p; }

    T *get(){ return r->p; }
    const T *get() const { return r->p; }

private:
    class rep
    {
    public:
        rep(T *p) : p(p), n(1) { }

        T *p;
        std::size_t n;
    };

    rep *r;
};

template<typename T> shared_ptr<T> to_shared_ptr(T *t){ return shared_ptr<T>(t); }

}

#endif // PCX_SHARED_PTR_H
