#include "pcx/textfile.h"

#include <fstream>

void pcx::textfile::read(std::ifstream &is, std::vector<std::string> &v)
{
    std::string s;
    while(std::getline(is, s))
    {
        v.push_back(s);
    }
}

bool pcx::textfile::read(const std::string &path, std::vector<std::string> &v)
{
    std::ifstream is(path);
    if(!is.is_open())
    {
        return false;
    }

    read(is, v);
    return true;
}

void pcx::textfile::write(std::ofstream &os, const std::vector<std::string> &v)
{
    for(auto &s: v)
    {
        os << s << "\n";
    }
}

bool pcx::textfile::write(const std::string &path, const std::vector<std::string> &v)
{
    std::ofstream os(path);
    if(!os.is_open())
    {
        return false;
    }

    write(os, v);
    return true;
}


