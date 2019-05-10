#ifndef PCX_SCOPED_COUNTER_H
#define PCX_SCOPED_COUNTER_H

#include <pcx/non_copyable.h>

namespace pcx
{

template<typename T> class scoped_counter_guard : public non_copyable
{
public:
    scoped_counter_guard(T &v) : v(&v) { ++v; }
    scoped_counter_guard(scoped_counter_guard &&g) : v(g.v) { g.v = nullptr; }
    ~scoped_counter_guard(){ if(v) --(*v); }

private:
    T *v;
};

template<typename T> scoped_counter_guard<T> scoped_counter(T &v)
{
    return scoped_counter_guard<T>(v);
}

}

#endif // PCX_SCOPED_COUNTER_H
