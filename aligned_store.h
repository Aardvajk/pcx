#ifndef PCX_ALIGNED_STORE_H
#define PCX_ALIGNED_STORE_H

#include <pcx/non_copyable.h>

#include <type_traits>
#include <utility>
#include <memory>

namespace pcx
{

template<std::size_t N> class aligned_store : public non_copyable
{
public:
    aligned_store() : df(nullptr) {} 
    ~aligned_store(){ if(df) df(&t); }

    template<typename T, typename... Args> T &alloc(Args&&... args){ static_assert(N >= sizeof(T), ""); new(&t) T(std::forward<Args>(args)...); df = [](void *p){ reinterpret_cast<T*>(p)->~T(); }; return get<T>(); }

    template<typename T> T &get(){ return *(reinterpret_cast<T*>(&t)); }
    template<typename T> const T &get() const { return *(reinterpret_cast<const T*>(&t)); }

private:
    typename std::aligned_storage<N>::type t;
    void(*df)(void*);
};

}

#endif // PCX_ALIGNED_STORE_H
