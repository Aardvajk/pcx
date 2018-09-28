#ifndef PCX_SIGNALS_H
#define PCX_SIGNALS_H

#include <pcx/non_copyable.h>

#include <vector>
#include <cstring>
#include <algorithm>

namespace pcx
{

template<typename... Args> class signal;

}

namespace pcx_detail_signals
{

class base_slot : public pcx::non_copyable
{
public:
    base_slot() = default;
    virtual ~base_slot() = default;
};

template<typename... Args> class abstract_slot : public base_slot
{
public:
    explicit abstract_slot(pcx::signal<Args...> *s) : s(s) { }
    virtual ~abstract_slot() override;
    
    virtual void call(Args... args) = 0;

    pcx::signal<Args...> *s;
};

template<typename T, typename... Args> class typed_slot : public abstract_slot<Args...>
{
public:
    explicit typed_slot(T *t, void(T::*f)(Args...), pcx::signal<Args...> *s);

    virtual void call(Args... args) override { (t->*f)(args...); }

private:
    T *t;
    void(T::*f)(Args...);
};

template<typename... Args> class signal_rep
{
public:
    signal_rep() : lock(false) { }
    ~signal_rep(){ for(auto &s: v) s->s = nullptr; }

    void call(Args... args);
    
    void add(abstract_slot<Args...> *s){ (lock ? a : v).push_back(s); }
    void remove(abstract_slot<Args...> *s);

private:
    bool lock;
    std::vector<abstract_slot<Args...>*> v, a;
};

template<typename... Args> constexpr abstract_slot<Args...> *null_slot(){ return nullptr; }

template<typename... Args> void signal_rep<Args...>::call(Args... args)
{
    lock = true;
    for(auto s: v) if(s) s->call(args...);

    v.erase(std::remove(v.begin(), v.end(), null_slot<Args...>()), v.end());

    v.insert(v.end(), a.begin(), a.end());
    a.clear();

    lock = false;
}

template<typename... Args> void signal_rep<Args...>::remove(abstract_slot<Args...> *s)
{
    if(lock)
    {
        std::replace(v.begin(), v.end(), s, null_slot<Args...>());
    }
    else
    {
        v.erase(std::remove(v.begin(), v.end(), s), v.end());
    }
}

template<typename... Args> class signal_accessor
{
public:
    explicit signal_accessor(pcx::signal<Args...> &s) : s(s) { }
    signal_rep<Args...> &operator()();

private:
    pcx::signal<Args...> &s;
};

}

namespace pcx
{

template<typename... Args> class signal : public non_copyable
{
public:
    void operator()(Args... args){ r.call(args...); }

private:
    friend class pcx_detail_signals::signal_accessor<Args...>;

    pcx_detail_signals::signal_rep<Args...> r;
};

class connections : public non_copyable
{
public:
    connections() = default;
    ~connections(){ for(auto s: v) delete s; }

    template<typename T, typename... Args> void connect(signal<Args...> &s, T *t, void(T::*f)(Args...)){ v.push_back(new pcx_detail_signals::typed_slot<T, Args...>(t, f, &s)); }

private:
    std::vector<pcx_detail_signals::base_slot*> v;
};

}

namespace pcx_detail_signals
{

template<typename... Args> signal_rep<Args...> &signal_accessor<Args...>::operator()()
{
    return s.r;
}

template<typename... Args> abstract_slot<Args...>::~abstract_slot()
{
    if(s)
    {
        signal_accessor<Args...>(*s)().remove(this);
    }
}

template<typename T, typename... Args> typed_slot<T, Args...>::typed_slot(T *t, void(T::*f)(Args...), pcx::signal<Args...> *s) : abstract_slot<Args...>(s), t(t), f(f)
{
    signal_accessor<Args...>(*s)().add(this);
}

}

#endif // PCX_SIGNALS_H
