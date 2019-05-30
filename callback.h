#ifndef PCX_CALLBACK_H
#define PCX_CALLBACK_H

#include <pcx/shared_data.h>

namespace pcx
{

namespace detail
{

template<typename R, typename... Args> class base_callback
{
public:
    virtual ~base_callback(){ }

    virtual R operator()(Args... args) const = 0;
};

template<typename T, typename R, typename... Args> class typed_callback : public base_callback<R, Args...>
{
public:
    typed_callback(T *t, R(T::*f)(Args...)) : t(t), f(f) { }

    virtual R operator()(Args... args) const { return (t->*f)(args...); }

private:
    T *t;
    R(T::*f)(Args...);
};

template<typename T, typename R, typename... Args> class const_typed_callback : public base_callback<R, Args...>
{
public:
    const_typed_callback(T *t, R(T::*f)(Args...) const ) : t(t), f(f) { }

    virtual R operator()(Args... args) const { return (t->*f)(args...); }

private:
    T *t;
    R(T::*f)(Args...) const;
};

}

template<typename R, typename... Args> class callback
{
public:
    callback(detail::base_callback<R, Args...> *c) : d(c) { }

    R operator()(Args... args) const { return d.value().c->operator()(args...); }

private:
    struct data
    {
        ~data(){ delete c; }

        detail::base_callback<R, Args...> *c;
    };

    shared_data<data> d;
};

template<typename T, typename R, typename... Args> callback<R, Args...> make_callback(T *owner, R(T::*method)(Args...))
{
    return callback<R, Args...>(new detail::typed_callback<T, R, Args...>(owner, method));
}

template<typename T, typename R, typename... Args> callback<R, Args...> make_callback(T *owner, R(T::*method)(Args...) const)
{
    return callback<R, Args...>(new detail::const_typed_callback<T, R, Args...>(owner, method));
}

}

#endif // PCX_CALLBACK_H
