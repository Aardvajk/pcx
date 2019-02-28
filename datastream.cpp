#include "pcx/datastream.h"

pcx::data_istream &operator>>(pcx::data_istream &ds, std::string &s)
{
    std::vector<char> v;

    ds >> v;
    v.push_back('\0');
    s = v.data();

    return ds;
}

pcx::data_ostream &operator<<(pcx::data_ostream &ds, const std::string &s)
{
    ds << static_cast<std::size_t>(s.length());
    ds.write(s.data(), s.length());

    return ds;
}

pcx::data_ostream &operator<<(pcx::data_ostream &ds, const char *s)
{
    return ds << std::string(s);
}
