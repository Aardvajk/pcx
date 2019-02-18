#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <iostream>
#include <fstream>
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
    template<typename T> data_istream &pod(T &v){ s->read(reinterpret_cast<char*>(&v), sizeof(T)); return *this; }

    std::istream *s;
};

class data_ifstream : public data_istream
{
public:
    data_ifstream(const std::string &path) : data_istream(&i), i(path) { }

    bool is_open() const { return i.is_open(); }

private:
    std::ifstream i;
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

    void write(const char *ch, std::size_t bytes){ s->write(ch, bytes); }

private:
    template<typename T> data_ostream &pod(const T &v){ s->write(reinterpret_cast<const char*>(&v), sizeof(T)); return *this; }

    std::ostream *s;
};

class data_ofstream : public data_ostream
{
public:
    data_ofstream(const std::string &path) : data_ostream(&o), o(path) { }

    bool is_open() const { return o.is_open(); }

private:
    std::ofstream o;
};

}

template<typename T> pcx::data_istream &operator>>(pcx::data_istream &ds, std::vector<T> &v)
{
    auto n = ds.get<std::size_t>();
    v.resize(n);

    ds.read(reinterpret_cast<char*>(v.data()), n * sizeof(T));

    return ds;
}

template<typename T> pcx::data_ostream &operator<<(pcx::data_ostream &ds, const std::vector<T> &v)
{
    ds << static_cast<std::size_t>(v.size());
    ds.write(reinterpret_cast<const char*>(v.data()), v.size() * sizeof(T));

    return ds;
}

inline pcx::data_istream &operator>>(pcx::data_istream &ds, std::string &s)
{
    std::vector<char> v;

    ds >> v;
    v.push_back('\0');
    s = v.data();

    return ds;
}

inline pcx::data_ostream &operator<<(pcx::data_ostream &ds, const std::string &s)
{
    ds << static_cast<std::size_t>(s.length());
    ds.write(s.data(), s.length());

    return ds;
}

#endif // DATASTREAM_H