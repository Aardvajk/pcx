#ifndef PCX_BASE64_H
#define PCX_BASE64_H

#include <string>

namespace pcx
{

namespace base64
{

std::string encode(const std::string &data);
std::string decode(const std::string &data);

}

}

#endif // PCX_BASE64_H
