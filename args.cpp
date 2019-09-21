#include "pcx/args.h"

#include <iostream>
#include <algorithm>

pcx::args::args()
{
}

pcx::args::args(int argc, char *argv[], std::vector<std::string> &args)
{
    int i = 1;
    for(; i < argc && argv[i][0] == '-'; ++i)
    {
        process(std::string(argv[i]).substr(1));
    }

    for(; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }
}

void pcx::args::process(const std::string &option)
{
    std::string s = option;
    std::string v;

    auto eq = s.find("+=");
    if(eq != std::string::npos)
    {
        v = s.substr(eq + 2);
        s = s.substr(0, eq);

        if(std::find(m[s].begin(), m[s].end(), v) == m[s].end())
        {
            m[s].push_back(v);
        }
    }
    else
    {
        auto eq = s.find("-=");
        if(eq != std::string::npos)
        {
            v = s.substr(eq + 2);
            s = s.substr(0, eq);

            auto i = m.find(s);
            if(i != m.end())
            {
                i->second.erase(std::remove(i->second.begin(), i->second.end(), v), i->second.end());
            }
        }
        else
        {
            auto eq = s.find("=");
            if(eq != std::string::npos)
            {
                v = s.substr(eq + 1);
                s = s.substr(0, eq);

                m[s] = { v };
            }
            else
            {
                if(m.find(s) == m.end())
                {
                    m[s] = { };
                }
            }
        }
    }
}

bool pcx::args::contains(const std::string &name) const
{
    return m.find(name) != m.end();
}

std::vector<std::string> pcx::args::operator[](const std::string &name) const
{
    auto i = m.find(name);
    return i == m.end() ? std::vector<std::string>() : i->second;
}

std::vector<std::string> pcx::args::keys() const
{
    std::vector<std::string> v;
    for(auto &s: m)
    {
        v.push_back(s.first);
    }

    return v;
}
