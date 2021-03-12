#ifndef PCX_FORMAT_H
#define PCX_FORMAT_H

#include <pcx/str.h>

namespace pcx
{

namespace format
{

namespace detail
{

std::string banner_imp(std::string title, char ch);

}

template<typename... Args> std::string banner(Args&&... args)
{
    return detail::banner_imp(pcx::str(std::forward<Args>(args)...), '=');
}

inline std::string banner(){ return banner(""); }

std::size_t padw(std::size_t n);

template<typename T> std::string pad(const T &text, std::size_t width)
{
    auto s = str(text);
    while(s.length() < width)
    {
        s = ' ' + s;
    }

    return s;
}

}

}

#endif // PCX_FORMAT_H
