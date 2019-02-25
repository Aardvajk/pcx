#ifndef PCX_FIXED_ARRAY_H
#define PCX_FIXED_ARRAY_H

#include <initializer_list>
#include <cstring>

namespace pcx
{

template<typename T, unsigned int max> class fixed_array
{
public:
    typedef std::size_t size_type;
    typedef T *iterator;
    typedef const T *const_iterator;

    fixed_array() : n(0) { }
    fixed_array(std::initializer_list<T> p) : n(0) { for(auto i: p) v[n++] = i; }
    explicit fixed_array(size_type size) : n(size) { }

    bool empty() const { return n == 0; }

    void clear(){ n = 0; }

    T &operator[](size_type i){ return v[i]; }
    const T &operator[](size_type i) const { return v[i]; }

    void push_back(const T &t){ v[n++] = t; }
    T pop_back(){ return v[--n]; }

    size_type size() const { return n; }
    size_type capacity() const { return max; }

    iterator begin(){ return v; }
    iterator end(){ return v + n; }

    const_iterator begin() const { return v; }
    const_iterator end() const { return v + n; }

private:
    T v[max];
    size_type n;
};

}

#endif // PCX_FIXED_ARRAY_H
