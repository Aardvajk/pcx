#ifndef PCX_SCOPED_PUSH_H
#define PCX_SCOPED_PUSH_H

#include <pcx/non_copyable.h>

namespace pcx
{

template<typename T> class scoped_push_guard : public non_copyable
{
public:
    scoped_push_guard(T &v, const typename T::value_type &t) : v(&v) { v.push_back(t); }
    scoped_push_guard(scoped_push_guard &&g) : v(g.v) { g.v = nullptr; }
    ~scoped_push_guard(){ if(v) v->pop_back(); }

private:
    T *v;
};

template<typename T> scoped_push_guard<T> scoped_push(T &v, const typename T::value_type &t)
{
    return scoped_push_guard<T>(v, t);
}

}

#endif // PCX_SCOPED_PUSH_H
