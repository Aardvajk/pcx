#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <utility>

namespace pcx
{

template<typename T> class shared_data
{
private:
    class rep
    {
    public:
        rep(const T &v) : n(1), v(v) { }
        template<typename... Args> rep(Args&&... args) : n(1), v({ std::forward<Args>(args)... }) { }

        unsigned n;
        T v;
    };

public:
    template<typename... Args> shared_data(Args&&... args) : r(new rep(std::forward<Args>(args)...)) { }
    shared_data(const shared_data &s) : r(s.r) { ++r->n; }
    shared_data(shared_data &&s) : r(s.r) { s.r = nullptr; }
    ~shared_data(){ if(r && !--r->n) delete r; }

    shared_data &operator=(const shared_data &s){ if(this != &s){ if(!--r->n) delete r; r = s.r; ++r->n; } return *this; }
    shared_data &operator=(shared_data &&s){ if(this != &s){ if(!--r->n) delete r; r = s.r; s.r = nullptr; } return *this; }

    T &value(){ detach(); return r->v; }
    const T &value() const { return r->v; }

private:
    void detach(){ if(r->n > 1){ auto n = new rep(r->v); --r->n; r = n; } }

    rep *r;
};

}

#endif // SHARED_DATA_H
