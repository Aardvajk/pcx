#ifndef PCX_ARGS_H
#define PCX_ARGS_H

#include <string>
#include <unordered_map>
#include <vector>

namespace pcx
{

class args
{
public:
    args(int argc, char *argv[], std::vector<std::string> &args);

    bool contains(const std::string &name) const;
    std::string operator[](const std::string &name) const;

private:
    std::unordered_map<std::string, std::string> m;
};

}

#endif // PCX_ARGS_H
