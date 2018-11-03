#ifndef PCX_SCOPED_PTR_H
#define PCX_SCOPED_PTR_H

namespace pcx
{

template<typename T> class scoped_ptr
{
public:
    scoped_ptr(T *t = nullptr) : t(t) { }
    scoped_ptr(scoped_ptr &p) : t(p.release()) { }
    scoped_ptr(scoped_ptr &&p) : t(p.release()) { }
    ~scoped_ptr(){ delete t; }

    scoped_ptr &operator=(T *p){ if(t != p){ delete t; t = p; } return *this; }
    scoped_ptr &operator=(scoped_ptr &p){ if(t != p.t){ delete t; t = p.release(); } return *this; }
    scoped_ptr &operator=(scoped_ptr &&p){ if(t != p.t){ delete t; t = p.release(); } return *this; }

    bool operator==(const T *v) const { return t == v; }
    bool operator!=(const T *v) const { return t != v; }

    operator bool() const { return t; }

    T *operator->(){ return t; }
    const T *operator->() const { return t; }

    T &operator*(){ return *t; }
    const T &operator*() const { return *t; }

    T *get(){ return t; }
    const T *get() const { return t; }

    T &ref(){ return *t; }
    const T &ref() const { return *t; }

    T *release(){ T *p = t; t = nullptr; return p; }
    void destroy(){ delete t; t = nullptr; }

private:
    T *t;
};

template<typename T> scoped_ptr<T> to_scoped_ptr(T *t){ return scoped_ptr<T>(t); }

}

#endif // PCX_SCOPED_PTR_H
