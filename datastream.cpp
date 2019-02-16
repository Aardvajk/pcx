#include "pcx/datastream.h"

#include <vector>

pcx::data_istream &operator>>(pcx::data_istream &ds, std::string &s)
{
    auto n = ds.get<std::size_t>();

    std::vector<char> v(n);
    ds.read(v.data(), n);

    v.push_back('\0');
    s = v.data();

    return ds;
}

pcx::data_ostream &operator<<(pcx::data_ostream &ds, const std::string &s)
{
    ds << static_cast<std::size_t>(s.length());
    ds.write(s.c_str(), s.length());

    return ds;
}
