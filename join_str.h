#ifndef PCX_JOIN_STR_H
#define PCX_JOIN_STR_H

#include <string>

#include <pcx/lexical_cast.h>

namespace pcx_detail
{

// hmm

struct lexical_functor
{
    template<typename T> std::string operator()(const T &t) const { return pcx::lexical_cast<std::string>(t); }
};

}

namespace pcx
{

template<typename T, typename C = pcx_detail::lexical_functor> std::string join_str(const T &t, const std::string &sep = " ", const C &c = pcx_detail::lexical_functor())
{
    std::string s;

    auto i = t.begin();
    while(i != t.end())
    {
        s += c(*i++);
        if(i != t.end())
        {
            s += sep;
        }
    }

    return s;
}

}

#endif // PCX_JOIN_STR_H
