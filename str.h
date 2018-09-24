#ifndef PCX_STR_H
#define PCX_STR_H

#include <string>
#include <sstream>

namespace pcx_detail
{

inline void str_detail(std::ostream &os)
{
}

template<typename T> void str_detail(std::ostream &os, const T &t)
{
    os << t;
}

template<typename T, typename... Args> void str_detail(std::ostream &os, const T &t, const Args&... args)
{
    os << t;
    str_detail(os, args...);
}

}

namespace pcx
{

template<typename... Args> std::string str(const Args&... args)
{
    std::ostringstream os;
    pcx_detail::str_detail(os, args...);

    return os.str();
}

}

#endif // PCX_STR_H
