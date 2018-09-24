#ifndef PCX_ALIGNED_STORE_H
#define PCX_ALIGNED_STORE_H

#include <type_traits>
#include <utility>
#include <memory>

namespace pcx
{

template<std::size_t N> class aligned_store
{
public:
    template<typename T> void alloc(){ static_assert(N >= sizeof(T), ""); new(&t) T(); }
    template<typename T, typename... Args> void alloc(Args&&... args){ static_assert(N >= sizeof(T), ""); new(&t) T(std::forward<Args>(args)...); }

    template<typename T> T &get(){ return *(reinterpret_cast<T*>(&t)); }
    template<typename T> const T &get() const { return *(reinterpret_cast<const T*>(&t)); }

private:
    typename std::aligned_storage<N>::type t;
};

}

#endif // PCX_ALIGNED_STORE_H
