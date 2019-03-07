#ifndef PCX_SPLIT_STR_H
#define PCX_SPLIT_STR_H

#include <string>
#include <vector>

namespace pcx
{

enum class split_mode
{
    keep_empty_sections,
    skip_empty_sections
};

std::vector<std::string> split_str(const std::string &s, const std::string &sep, split_mode mode = split_mode::skip_empty_sections);

}

#endif // PCX_SPLIT_STR_H
