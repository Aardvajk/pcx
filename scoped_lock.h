#ifndef PCX_SCOPED_LOCK_H
#define PCX_SCOPED_LOCK_H

#include <pcx/non_copyable.h>

namespace pcx
{

template<typename T> struct scoped_lock_value
{
    static const T locked = static_cast<T>(1);
    static const T unlocked = static_cast<T>(0);
};

template<typename T> class scoped_lock_guard : public non_copyable
{
public:
    explicit scoped_lock_guard(T &v) : v(&v) { v = scoped_lock_value<T>::locked; }
    scoped_lock_guard(scoped_lock_guard &&o) : v(o.v) { o.v = nullptr; }
    ~scoped_lock_guard(){ if(v) *v = scoped_lock_value<T>::unlocked; }

    T value() const { return v ? *v : scoped_lock_value<T>::unlocked; }

private:
    T *v;
};

template<typename T> scoped_lock_guard<T> scoped_lock(T &v)
{
    return scoped_lock_guard<T>(v);
}

class lock
{
public:
    lock(bool value = false) : v(value) { }

    operator bool() const { return v; }

private:
    bool v;
};

template<> struct scoped_lock_value<lock>
{
    static const lock locked;
    static const lock unlocked;
};

}

#endif // PCX_SCOPED_LOCK_H
