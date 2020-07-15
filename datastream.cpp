#include "pcx/datastream.h"

pcx::data_istream &operator>>(pcx::data_istream &ds, std::string &s)
{
    std::vector<char> v;

    ds >> v;
    v.push_back('\0');
    s = v.data();

    return ds;
}

void pcx::data_ostream_patch_base::update(const char *v)
{
    if(s)
    {
        s->writeAt(p, v, n);
    }
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

pcx::data_ostream &pcx::data_ostream::operator<<(data_ostream_patch_base &v)
{
    v.s = this;
    v.p = position();

    for(std::size_t i = 0; i < v.n; ++i)
    {
        s->put(char(0));
    }

    return *this;
}

void pcx::data_ostream::writeAt(std::size_t position, const char *ch, std::size_t bytes)
{
    auto old = s->tellp();
    s->seekp(std::streamoff(position));

    write(ch, bytes);

    s->seekp(old);
}
