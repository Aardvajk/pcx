#ifndef PCX_ENUM_RANGE_H
#define PCX_ENUM_RANGE_H

namespace pcx
{

template<typename T> class enum_range_iterator
{
public:
    enum_range_iterator(T t) : t(t) { }

    bool operator==(const enum_range_iterator &o) const { return t == o.t; }
    bool operator!=(const enum_range_iterator &o) const { return t != o.t; }

    enum_range_iterator &operator++(){ t = static_cast<T>(static_cast<unsigned>(t) + 1); return *this; }
    enum_range_iterator operator++(int){ auto r = *this; t = static_cast<T>(static_cast<unsigned>(t) + 1); return r; }

    T operator*() const { return t; }
    const T *operator->() const { return &t; }

private:
    T t;
};

template<typename T> class enum_range_wrapper
{
public:
    enum_range_wrapper(T start, T finish) : start(start), finish(finish) { }

    enum_range_iterator<T> begin(){ return enum_range_iterator<T>(start); }
    enum_range_iterator<T> end(){ return enum_range_iterator<T>(static_cast<T>(static_cast<unsigned>(finish) + 1)); }

private:
    T start;
    T finish;
};

template<typename T> enum_range_wrapper<T> enum_range(T start, T finish)
{
    return enum_range_wrapper<T>(start, finish);
}

}

#endif // PCX_ENUM_RANGE_H
