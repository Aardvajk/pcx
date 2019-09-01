#include "pcx/args.h"

#include <iostream>

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

    auto eq = s.find_first_of('=');
    if(eq != std::string::npos)
    {
        v = s.substr(eq + 1);
        s = s.substr(0, eq);
    }

    m[s].push_back(v);
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
