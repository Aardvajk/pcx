#ifndef PCX_RANGE_REVERSE_H
#define PCX_RANGE_REVERSE_H

namespace pcx
{

template<typename T> class range_reverse_wrapper
{
public:
    range_reverse_wrapper(T &v) : v(v) { }

    typename T::reverse_iterator begin(){ return v.rbegin(); }
    typename T::reverse_iterator end(){ return v.rend(); }

    typename T::const_reverse_iterator begin() const { return v.rbegin(); }
    typename T::const_reverse_iterator end() const { return v.rend(); }

private:    
    T &v;
};

template<typename T> range_reverse_wrapper<T> range_reverse(T &v)
{
    return range_reverse_wrapper<T>(v);
}

template<typename T> class range_reverse_const_wrapper
{
public:
    range_reverse_const_wrapper(const T &v) : v(v) { }

    typename T::const_reverse_iterator begin() const { return v.rbegin(); }
    typename T::const_reverse_iterator end() const { return v.rend(); }

private:    
    const T &v;
};

template<typename T> range_reverse_const_wrapper<T> range_reverse(const T &v)
{
    return range_reverse_const_wrapper<T>(v);
}

}

#endif // PCX_RANGE_REVERSE_H
