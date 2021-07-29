#pragma once
#include <string>

class IPacket
{
public:
    virtual ~IPacket() = default;
    virtual std::string GetData() const = 0;
    virtual size_t GetSize() const = 0;
};