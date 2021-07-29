#pragma once
#include "packet.h"

class BaseDataPacket : public IPacket
{
public:
    BaseDataPacket(const std::string &message)
        : m_message{message}
    {
    }

    std::string GetData() const override
    {
        return m_message;
    }

    size_t GetSize() const override
    {
        return m_message.size();
    }

private:
    std::string m_message;
};
