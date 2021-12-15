#ifndef PCX_ARGS_H
#define PCX_ARGS_H

#include <string>
#include <unordered_map>
#include <vector>

namespace pcx
{

class args
{
public:
    args();
    args(int argc, char *argv[], std::vector<std::string> &args);
    ~args();

    void push();
    void pop();

    void process(const std::string &option);
    bool readFromFile(const std::string &path);

    bool contains(const std::string &name) const;
    bool contains(const std::string &name, const std::string &value) const;

    std::vector<std::string> operator[](const std::string &name) const;

    std::vector<std::string> keys() const;

private:
    std::vector<std::unordered_map<std::string, std::vector<std::string> > > mv;
};

}

#endif // PCX_ARGS_H
