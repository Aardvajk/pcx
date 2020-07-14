#ifndef INDEXED_SET_H
#define INDEXED_SET_H

#include <vector>
#include <unordered_map>

namespace pcx
{

template<typename T, typename Hash = std::hash<T> > class indexed_set
{
public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using size_type = typename std::vector<T>::size_type;

    indexed_set(){ }

    std::size_t insert(const T &s);

    T &operator[](std::size_t index){ return v[index]; }
    const T &operator[](std::size_t index) const { return v[index]; }

    iterator begin(){ return v.begin(); }
    iterator end(){ return v.end(); }

    const_iterator begin() const { return v.begin(); }
    const_iterator end() const { return v.end(); }

    size_type size() const { return v.size(); }

private:
    std::vector<T> v;
    std::unordered_map<T, size_type, Hash> m;
};

template<typename T, typename Hash> std::size_t indexed_set<T, Hash>::insert(const T &s)
{
    auto i = m.find(s);
    if(i != m.end())
    {
        return i->second;
    }

    v.push_back(s);
    return static_cast<std::size_t>(m[s] = v.size() - 1);
}

}

#endif // INDEXED_SET_H
