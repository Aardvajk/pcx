#ifndef PCX_FORMAT_H
#define PCX_FORMAT_H

#include <pcx/str.h>

namespace pcx
{

namespace format
{

inline std::size_t padw(std::size_t n) { return n ? pcx::str(n - 1).length() : 1; }

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
