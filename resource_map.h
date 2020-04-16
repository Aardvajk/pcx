#ifndef PCX_RESOURCE_MAP_H
#define PCX_RESOURCE_MAP_H

#include <pcx/non_copyable.h>
#include <pcx/optional.h>
#include <pcx/ptr_vector.h>

#include <vector>
#include <iostream>

namespace pcx
{

template<typename Base> class resource_map;
template<typename Base, typename T> class resource_handle;

namespace detail
{

template<typename Base> class base_resource_handle : public non_copyable
{
protected:
    Base &access(resource_map<Base> &map, std::size_t id){ return map.v[id]; }
    const Base &access(const resource_map<Base> &map, std::size_t id) const { return map.v[id]; }
};

}

template<typename Base, typename T> class resource_handle : public detail::base_resource_handle<Base>
{
public:
    resource_handle() = default;
    resource_handle(resource_handle &&o) : map(o.map), id(o.id) { o.id = pcx::nullopt; }
    ~resource_handle(){ if(id) map->remove(*this); }

    resource_handle &operator=(resource_handle &&o);

    T &operator*(){ return static_cast<T&>(detail::base_resource_handle<Base>::access(*map, *id)); }
    const T &operator*() const { return static_cast<const T&>(detail::base_resource_handle<Base>::access(*map, *id)); }

    T *get(){ return &(*(*this)); }
    const T *get() const { return &(*(*this)); }

    T *operator->(){ return &(*(*this)); }
    const T *operator->() const { return &(*(*this)); }

    bool valid() const { return id; }

public:
    friend class resource_map<Base>;

    resource_handle(resource_map<Base> *map, std::size_t id) : map(map), id(id) { }

    resource_map<Base> *map;
    pcx::optional<std::size_t> id;
};

template<typename Base, typename T> resource_handle<Base, T> &resource_handle<Base, T>::operator=(resource_handle<Base, T> &&o)
{
    if(id) map->remove(*this);

    map = o.map;
    id = o.id;

    o.id = nullopt;
    return *this;
}

template<typename Base> class resource_map : public non_copyable
{
public:
    using iterator = typename ptr_view_vector<Base>::iterator;
    using const_iterator = typename ptr_view_vector<Base>::const_iterator;

    resource_map() = default;

    template<typename T> resource_handle<Base, T> add(T *p);
    template<typename T> void remove(const resource_handle<Base, T> &id);

    iterator begin(){ return v.begin(); }
    iterator end(){ return v.end(); }

    const_iterator begin() const { return v.begin(); }
    const_iterator end() const { return v.end(); }

private:
    friend class detail::base_resource_handle<Base>;

    ptr_view_vector<Base> v;
    std::vector<std::size_t> fr;
};

template<typename Base> template<typename T> resource_handle<Base, T> resource_map<Base>::add(T *p)
{
    if(!fr.empty())
    {
        auto id = fr.back();
        fr.pop_back();

        v.replace_ptr(id, p);
        return resource_handle<Base, T>(this, id);
    }

    v.push_back(p);
    return resource_handle<Base, T>(this, v.size() - 1);
}

template<typename Base> template<typename T> void resource_map<Base>::remove(const resource_handle<Base, T> &id)
{
    auto i = *(id.id);

    delete v.ptr(i);
    v.replace_ptr(i, nullptr);

    fr.push_back(i);
}

}

#endif // PCX_RESOURCE_MAP_H
