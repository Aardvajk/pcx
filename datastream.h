#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <pcx/buffer.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace pcx
{

class data_istream
{
public:
    explicit data_istream(std::istream *s) : s(s) { }

    data_istream &operator>>(char &v){ return pod(v); }
    data_istream &operator>>(unsigned char &v){ return pod(v); }
    data_istream &operator>>(short &v){ return pod(v); }
    data_istream &operator>>(unsigned short &v){ return pod(v); }
    data_istream &operator>>(int &v){ return pod(v); }
    data_istream &operator>>(unsigned int &v){ return pod(v); }
    data_istream &operator>>(long &v){ return pod(v); }
    data_istream &operator>>(unsigned long &v){ return pod(v); }
    data_istream &operator>>(long long &v){ return pod(v); }
    data_istream &operator>>(unsigned long long &v){ return pod(v); }
    data_istream &operator>>(float &v){ return pod(v); }
    data_istream &operator>>(double v){ return pod(v); }

    void read(char *ch, std::size_t bytes){ s->read(ch, bytes); }

    template<typename T> T get(){ T v = T(); (*this) >> v; return v; }

private:
    template<typename T> data_istream &pod(T &v){ s->read(reinterpret_cast<char*>(&v), sizeof(T)); if(s->fail()) throw 0; return *this; }

    std::istream *s;
};

class data_ifstream : public data_istream
{
public:
    data_ifstream(const std::string &path) : data_istream(&i), i(path, std::ios::binary) { }

    bool is_open() const { return i.is_open(); }

private:
    std::ifstream i;
};

class data_isstream : public data_istream
{
public:
    data_isstream(const buffer &data) : data_istream(&i), i(std::string(data.begin(), data.end()), std::ios::binary) { }

private:
    std::istringstream i;
};

class data_ostream;

class data_ostream_patch_base
{
public:
    explicit data_ostream_patch_base(std::size_t n) : n(n) { }

protected:
    void update(data_ostream &s, const char *v);

private:
    friend class data_ostream;

    std::size_t n, p;
};

template<typename T> class data_ostream_patch : public data_ostream_patch_base
{
public:
    data_ostream_patch() : data_ostream_patch_base(sizeof(T)) { }

    void assign(data_ostream &s, const T &v){ update(s, reinterpret_cast<const char*>(&v)); }
};

class data_ostream
{
public:
    explicit data_ostream(std::ostream *s) : s(s) { }

    data_ostream &operator<<(char v){ return pod(v); }
    data_ostream &operator<<(unsigned char v){ return pod(v); }
    data_ostream &operator<<(short v){ return pod(v); }
    data_ostream &operator<<(unsigned short v){ return pod(v); }
    data_ostream &operator<<(int v){ return pod(v); }
    data_ostream &operator<<(unsigned int v){ return pod(v); }
    data_ostream &operator<<(long v){ return pod(v); }
    data_ostream &operator<<(unsigned long v){ return pod(v); }
    data_ostream &operator<<(long long v){ return pod(v); }
    data_ostream &operator<<(unsigned long long v){ return pod(v); }
    data_ostream &operator<<(float v){ return pod(v); }
    data_ostream &operator<<(double v){ return pod(v); }

    data_ostream &operator<<(data_ostream_patch_base &v);

    void write(const char *ch, std::size_t bytes){ s->write(ch, bytes); }
    void writeAt(std::size_t position, const char *ch, std::size_t bytes);

    std::size_t position() const { return std::size_t(s->tellp()); }

private:
    template<typename T> data_ostream &pod(const T &v){ s->write(reinterpret_cast<const char*>(&v), sizeof(T)); return *this; }

    std::ostream *s;
};

class data_ofstream : public data_ostream
{
public:
    data_ofstream(const std::string &path) : data_ostream(&o), o(path, std::ios::binary) { }

    bool is_open() const { return o.is_open(); }

private:
    std::ofstream o;
};

class data_osstream : public data_ostream
{
public:
    data_osstream() : data_ostream(&o), o(std::ios::binary) { }

    buffer data() const { auto s = o.str(); return buffer(s.begin(), s.end()); }

private:
    std::ostringstream o;
};

}

template<typename T> pcx::data_istream &operator>>(pcx::data_istream &ds, std::vector<T> &v)
{
    v.clear();

    auto n = ds.get<std::size_t>();
    for(std::size_t i = 0; i < n; ++i) v.push_back(ds.get<T>());

    return ds;
}

template<> inline pcx::data_istream &operator>>(pcx::data_istream &ds, std::vector<char> &v)
{
    auto n = ds.get<std::size_t>();
    v.resize(n);

    ds.read(reinterpret_cast<char*>(v.data()), n);

    return ds;
}

template<typename T> pcx::data_ostream &operator<<(pcx::data_ostream &ds, const std::vector<T> &v)
{
    ds << static_cast<std::size_t>(v.size());
    for(auto i: v) ds << i;

    return ds;
}

template<> inline pcx::data_ostream &operator<<(pcx::data_ostream &ds, const std::vector<char> &v)
{
    ds << static_cast<std::size_t>(v.size());
    ds.write(reinterpret_cast<const char*>(v.data()), v.size());

    return ds;
}

pcx::data_istream &operator>>(pcx::data_istream &ds, std::string &s);
pcx::data_ostream &operator<<(pcx::data_ostream &ds, const std::string &s);

pcx::data_ostream &operator<<(pcx::data_ostream &ds, const char *s);

#endif // DATASTREAM_H
