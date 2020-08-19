#include "pcx/datastream.h"

std::vector<char> pcx::data_istream::all()
{
    return { std::istreambuf_iterator<char>(*s), std::istreambuf_iterator<char>() };
}

void pcx::data_ostream_patch_base::update(data_ostream &s, const char *v)
{
    s.writeAt(p, v, n);
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
