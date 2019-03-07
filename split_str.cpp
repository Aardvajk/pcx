#include "pcx/split_str.h"

std::vector<std::string> pcx::split_str(const std::string &s, const std::string &sep, split_mode mode)
{
    std::vector<std::string> r;

    std::string b;
    std::string::size_type i = 0;

    while(i < s.length())
    {
        if(sep.find(s[i]) != std::string::npos)
        {
            if(i || mode == split_mode::keep_empty_sections)
            {
                if(mode == split_mode::keep_empty_sections || !b.empty())
                {
                    r.push_back(b);
                }

                b.clear();
            }

            if(i == s.length() - 1 && mode == split_mode::keep_empty_sections)
            {
                r.push_back({ });
            }
        }
        else
        {
            b.push_back(s[i]);
        }

        ++i;
    }

    if(!b.empty())
    {
        r.push_back(b);
    }

    return r;
}
