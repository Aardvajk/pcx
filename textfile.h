#ifndef PCX_TEXTFILE_H
#define PCX_TEXTFILE_H

#include <vector>
#include <string>
#include <iostream>

namespace pcx
{

namespace textfile
{

void read(std::ifstream &is, std::vector<std::string> &v);
bool read(const std::string &path, std::vector<std::string> &v);

void write(std::ofstream &os, const std::vector<std::string> &v);
bool write(const std::string &path, const std::vector<std::string> &v);

}

}

#endif // PCX_TEXTFILE_H
