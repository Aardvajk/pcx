#ifndef PCX_PTR_VECTOR_H
#define PCX_PTR_VECTOR_H

#include <vector>

namespace pcx
{

template<typename T, typename A = std::allocator<T*> > class ptr_vector
{
public:
    using size_type = typename std::vector<T*, A>::size_type;

    class iterator
    {
    public:
        explicit iterator(typename std::vector<T*>::iterator i) : i(i) { }

        bool operator==(const iterator &o) const { return i == o.i; }
        bool operator!=(const iterator &o) const { return i != o.i; }

        iterator operator+(size_type s) const { return iterator(i + s); }
        iterator operator-(size_type s) const { return iterator(i - s); }

        iterator &operator++(){ ++i; return *this; }
        iterator operator++(int){ return iterator(i++); }

        iterator &operator--(){ --i; return *this; }
        iterator operator--(int){ return iterator(i--); }

        T &operator*() const { return *(*i); }
        T *operator->() const { return *i; }

    private:
        typename std::vector<T*, A>::iterator i;
    };

    class const_iterator
    {
    public:
        explicit const_iterator(typename std::vector<T*, A>::const_iterator i) : i(i) { }

        bool operator==(const const_iterator &o) const { return i == o.i; }
        bool operator!=(const const_iterator &o) const { return i != o.i; }

        const_iterator operator+(size_type s) const { return const_iterator(i + s); }
        const_iterator operator-(size_type s) const { return const_iterator(i - s); }

        const_iterator &operator++(){ ++i; return *this; }
        const_iterator operator++(int){ return const_iterator(i++); }

        const_iterator &operator--(){ --i; return *this; }
        const_iterator operator--(int){ return const_iterator(i--); }

        const T &operator*() const { return *(*i); }
        const T *operator->() const { return *i; }

    private:
        typename std::vector<T*, A>::const_iterator i;
    };

    class reverse_iterator
    {
    public:
        explicit reverse_iterator(typename std::vector<T*>::reverse_iterator i) : i(i) { }

        bool operator==(const reverse_iterator &o) const { return i == o.i; }
        bool operator!=(const reverse_iterator &o) const { return i != o.i; }

        reverse_iterator operator+(size_type s) const { return reverse_iterator(i + s); }
        reverse_iterator operator-(size_type s) const { return reverse_iterator(i - s); }

        reverse_iterator &operator++(){ ++i; return *this; }
        reverse_iterator operator++(int){ return reverse_iterator(i++); }

        reverse_iterator &operator--(){ --i; return *this; }
        reverse_iterator operator--(int){ return reverse_iterator(i--); }

        T &operator*() const { return *(*i); }
        T *operator->() const { return *i; }

    private:
        typename std::vector<T*, A>::reverse_iterator i;
    };

    class const_reverse_iterator
    {
    public:
        explicit const_reverse_iterator(typename std::vector<T*, A>::const_reverse_iterator i) : i(i) { }

        bool operator==(const const_reverse_iterator &o) const { return i == o.i; }
        bool operator!=(const const_reverse_iterator &o) const { return i != o.i; }

        const_reverse_iterator operator+(size_type s) const { return const_reverse_iterator(i + s); }
        const_reverse_iterator operator-(size_type s) const { return const_reverse_iterator(i - s); }

        const_reverse_iterator &operator++(){ ++i; return *this; }
        const_reverse_iterator operator++(int){ return const_reverse_iterator(i++); }

        const_reverse_iterator &operator--(){ --i; return *this; }
        const_reverse_iterator operator--(int){ return const_reverse_iterator(i--); }

        const T &operator*() const { return *(*i); }
        const T *operator->() const { return *i; }

    private:
        typename std::vector<T*, A>::const_reverse_iterator i;
    };

    ptr_vector() = default;
    ~ptr_vector(){ for(auto &i: v) delete i; }

    void push_back(T *t){ v.push_back(t); }
    void pop_back(){ delete v.back(); v.pop_back(); }
    void clear(){ for(auto &i: v) delete i; v.clear(); }

    template<typename... Args> void emplace_back(Args&&... args){ v.push_back(new T(std::forward<Args>(args)...)); }

    iterator erase(iterator i){ delete *(i.i); return iterator(v.erase(i.i)); }
    iterator erase(iterator a, iterator b){ for(auto i = a; i != b; ++i) delete *(i.i); return iterator(v.erase(a.i, b.i)); }

    void insert_ptr(size_type index, T *t){ delete v[index]; v[index] = t; }
    void replace(T *before, T *after){ for(size_type i = 0; i < size(); ++i) if(ptr(i) == before){ insert_ptr(i, after); return; } }
    void replace_all(T *before, T *after){ for(size_type i = 0; i < size(); ++i) if(ptr(i) == before) insert_ptr(i, after); }

    T &operator[](size_type i){ return *(v[i]); }
    const T &operator[](size_type i) const { return *(v[i]); }

    T *ptr(size_type i){ return v[i]; }
    const T *ptr(size_type i) const { return v[i]; }

    iterator begin(){ return iterator(v.begin()); }
    iterator end(){ return iterator(v.end()); }

    const_iterator begin() const { return const_iterator(v.begin()); }
    const_iterator end() const { return const_iterator(v.end()); }

    reverse_iterator rbegin(){ return reverse_iterator(v.rbegin()); }
    reverse_iterator rend(){ return reverse_iterator(v.rend()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(v.rbegin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(v.rend()); }

    T &front(){ return *(v.front()); }
    const T &front() const { return *(v.front()); }

    T &back(){ return *(v.back()); }
    const T &back() const { return *(v.back()); }

    T *back_ptr(){ return v.back(); }
    const T *back_ptr() const { return v.back(); }

    size_type size() const { return v.size(); }
    bool empty() const { return v.empty(); }

    void remove_all(T *t){ auto i = v.begin(); while(i != v.end()){ if(*i == t){ delete *i; i = v.erase(i); } else ++i; } }

    T *release(size_type index){ T *t = v[index]; v[index] = nullptr; return t; }
    T *release_back(){ T *t = v.back(); v.pop_back(); }
    void release_all(T *t){ v.remove_all(t); }

    const std::vector<T*, A> &raw() const { return v; }

private:
    ptr_vector(const ptr_vector&) = delete;
    void operator=(const ptr_vector&) = delete;

    std::vector<T*, A> v;
};

}

#endif // PCX_PTR_VECTOR_H
