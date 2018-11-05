#ifndef PCX_ORDERED_MAP_H
#define PCX_ORDERED_MAP_H

#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

namespace pcx
{

template<typename K, typename V, typename Hash = std::hash<K> > class ordered_map
{
public:
    using iterator = typename std::vector<std::pair<K, V> >::iterator;
    using const_iterator = typename std::vector<std::pair<K, V> >::const_iterator;
    using size_type = typename std::vector<std::pair<K, V> >::size_type;

    ordered_map() = default;

    V &operator[](const K &key);

    std::pair<K, V> &operator[](size_type index){ return v[index]; }
    const std::pair<K, V> &operator[](size_type index) const { return v[index]; }

    void clear(){ m.clear(); v.clear(); }

    iterator find(const K &key){ return find_t<iterator, ordered_map>(*this, key); }
    const_iterator find(const K &key) const { return find_t<const_iterator, ordered_map>(*this, key); }

    iterator begin(){ return v.begin(); }
    iterator end(){ return v.end(); }

    const_iterator begin() const { return v.begin(); }
    const_iterator end() const { return v.end(); }

    size_type size() const { return v.size(); }

private:
    template<typename I, typename M> static I find_t(M &m, const K &key);

    class proxy
    {
    public:
        proxy(const std::vector<std::pair<K, V> > &v) : v(v) { }
        bool operator()(size_type i, const K &key) const { return v[i].first < key; }

    private:
        const std::vector<std::pair<K, V> > &v;
    };

    std::vector<std::pair<K, V> > v;
    std::unordered_map<std::size_t, std::vector<size_type> > m;
};

template<typename K, typename V, typename Hash> V &ordered_map<K, V, Hash>::operator[](const K &key)
{
    auto hc = Hash()(key);

    auto i = m.find(hc);
    if(i != m.end())
    {
        auto j = std::lower_bound(i->second.begin(), i->second.end(), key, proxy(v));
        if(*j < v.size() && v[*j].first == key)
        {
            return v[*j].second;
        }

        i->second.insert(j, v.size());
    }
    else
    {
        m.insert(std::make_pair(hc, std::vector<std::size_t>({ v.size() })));
    }

    v.push_back(std::make_pair(key, V()));
    return v.back().second;
}

template<typename K, typename V, typename Hash> template<typename I, typename M> I ordered_map<K, V, Hash>::find_t(M &m, const K &key)
{
    auto i = m.m.find(Hash()(key));
    if(i != m.m.end())
    {
        auto j = std::lower_bound(i->second.begin(), i->second.end(), key, proxy(m.v));
        if(*j < m.v.size() && m.v[*j].first == key)
        {
            return m.v.begin() + *j;
        }
    }

    return m.v.end();
}

}

#endif // PCX_ORDERED_MAP_H
