#ifndef PCX_INDEXED_RANGE_H
#define PCX_INDEXED_RANGE_H

namespace pcx
{

template<typename T> struct indexed_range_pair
{
    std::size_t index;
    typename T::value_type &value;
};

template<typename T> class indexed_range_iterator
{
public:
    indexed_range_iterator(typename T::iterator i, std::size_t s = 0) : i(i), s(s) { }

    bool operator==(const indexed_range_iterator &o) const { return i == o.i; }
    bool operator!=(const indexed_range_iterator &o) const { return i != o.i; }

    indexed_range_iterator &operator++(){ ++i; ++s; return *this; }

    indexed_range_pair<T> operator*() const { return { s, *i }; }

private:
    typename T::iterator i;
    size_t s;
};

template<typename T> class indexed_range_wrapper
{
public:
    indexed_range_wrapper(T &t) : t(t) {}

    indexed_range_iterator<T> begin(){ return indexed_range_iterator<T>(t.begin()); }
    indexed_range_iterator<T> end(){ return indexed_range_iterator<T>(t.end()); }

private:
    T &t;
};

template<typename T> indexed_range_wrapper<T> indexed_range(T &t)
{
    return indexed_range_wrapper<T>(t);
}

template<typename T> struct const_indexed_range_pair
{
    std::size_t index;
    const typename T::value_type &value;
};

template<typename T> class const_indexed_range_iterator
{
public:
    const_indexed_range_iterator(typename T::const_iterator i, std::size_t s = 0) : i(i), s(s) { }

    bool operator==(const const_indexed_range_iterator &o) const { return i == o.i; }
    bool operator!=(const const_indexed_range_iterator &o) const { return i != o.i; }

    const_indexed_range_iterator &operator++(){ ++i; ++s; return *this; }

    const_indexed_range_pair<T> operator*() const { return { s, *i }; }

private:
    typename T::const_iterator i;
    size_t s;
};

template<typename T> class const_indexed_range_wrapper
{
public:
    const_indexed_range_wrapper(const T &t) : t(t) {}

    const_indexed_range_iterator<T> begin() const { return const_indexed_range_iterator<T>(t.begin()); }
    const_indexed_range_iterator<T> end() const { return const_indexed_range_iterator<T>(t.end()); }

private:
    const T &t;
};

template<typename T> const_indexed_range_wrapper<T> indexed_range(const T &t)
{
    return const_indexed_range_wrapper<T>(t);
}

}

#endif // PCX_INDEXED_RANGE_H
