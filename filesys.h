#ifndef PCX_FILESYS_H
#define PCX_FILESYS_H

#include <string>
#include <vector>

namespace pcx
{

namespace filesys
{

bool exists(const std::string &path);

std::vector<std::string> find_files(const std::string &path);

}

}

#endif // PCX_FILESYS_H
