#ifndef PCX_LEXICAL_CAST_H
#define PCX_LEXICAL_CAST_H

#include <sstream>
#include <iomanip>

namespace pcx_detail
{

namespace detail_lexical_cast
{

template<typename T> std::string from(T t)
{
    std::ostringstream o;
    o << t;

    return o.str();
}

template<> inline std::string from<const char*>(const char *t){ return t; }
template<> inline std::string from<std::string&&>(std::string &&t){ return std::move(t); }

template<typename T> T to(std::string &&s)
{
    std::istringstream is(std::move(s));

    T t;
    is >> t;

    return is ? t : T();
}

template<> inline std::string to<std::string>(std::string &&s){ return std::move(s); }

}

}

namespace pcx
{

template<typename To, typename From> To lexical_cast(From f)
{
    return std::move(pcx_detail::detail_lexical_cast::to<To>(pcx_detail::detail_lexical_cast::from<From>(std::move(f))));
}

}

#endif // PCX_LEXICAL_CAST_H
