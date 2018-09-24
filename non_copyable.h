#ifndef PCX_NON_COPYABLE_H
#define PCX_NON_COPYABLE_H

namespace pcx
{

class non_copyable
{
public:
    non_copyable() = default;

private:
    non_copyable(const non_copyable&) = delete;
    non_copyable &operator=(non_copyable&) = delete;
};

}

#endif // PCX_NON_COPYABLE_H
