#ifndef PCX_FLAGS_H
#define PCX_FLAGS_H

#include <type_traits>
#include <initializer_list>
#include <cstdint>

namespace pcx
{

template<typename T> class flags
{
public:
    using type = typename std::underlying_type<T>::type;

    flags() : v(0) { }
    flags(T v) : v(static_cast<type>(v)) { }
    flags(std::initializer_list<T> vs) : v(0) { for(auto i: vs) v |= static_cast<type>(i); }

    operator bool() const { return v; }
    operator T() const { return static_cast<T>(v); }

    flags operator~() const { return static_cast<T>(~v); }

    flags &operator|=(flags f){ v |= f.v; return *this; }
    flags &operator&=(flags f){ v &= f.v; return *this; }
    flags &operator^=(flags f){ v ^= f.v; return *this; }

private:
    type v;
};

}

template<typename T> struct pcx_is_flag_enum : std::false_type { };

template<typename T> using pcx_detail_flag_type = typename std::enable_if<pcx_is_flag_enum<T>::value, T>::type;

template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator|(T a, T b){ return T(static_cast<typename pcx::flags<pcx_detail_flag_type<T> >::type>(a) | static_cast<typename pcx::flags<pcx_detail_flag_type<T> >::type>(b)); }
template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator&(T a, T b){ return T(static_cast<typename pcx::flags<pcx_detail_flag_type<T> >::type>(a) & static_cast<typename pcx::flags<pcx_detail_flag_type<T> >::type>(b)); }
template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator^(T a, T b){ return T(static_cast<typename pcx::flags<pcx_detail_flag_type<T> >::type>(a) ^ static_cast<typename pcx::flags<pcx_detail_flag_type<T> >::type>(b)); }

template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator~(T a){ return static_cast<T>(~static_cast<typename pcx::flags<pcx_detail_flag_type<T> >::type>(a)); }

template<typename T> pcx::flags<T> operator|(pcx::flags<T> a, pcx::flags<T> b){ return static_cast<T>(a) | static_cast<T>(b); }
template<typename T> pcx::flags<T> operator&(pcx::flags<T> a, pcx::flags<T> b){ return static_cast<T>(a) & static_cast<T>(b); }
template<typename T> pcx::flags<T> operator^(pcx::flags<T> a, pcx::flags<T> b){ return static_cast<T>(a) ^ static_cast<T>(b); }

template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator|(T a, pcx::flags<T> b){ return a | static_cast<T>(b); }
template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator&(T a, pcx::flags<T> b){ return a & static_cast<T>(b); }
template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator^(T a, pcx::flags<T> b){ return a ^ static_cast<T>(b); }

template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator|(pcx::flags<T> a, T b){ return static_cast<T>(a) | b; }
template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator&(pcx::flags<T> a, T b){ return static_cast<T>(a) & b; }
template<typename T> pcx::flags<pcx_detail_flag_type<T> > operator^(pcx::flags<T> a, T b){ return static_cast<T>(a) ^ b; }

#endif // PCX_FLAGS_H
