#pragma once
#include "packet.h"
#include <memory>

class TcpIpPacketDecorator : public IPacket
{
public:
    TcpIpPacketDecorator(const std::shared_ptr<IPacket> data)
        : m_data{data}
    {
    }

protected:
    std::shared_ptr<IPacket> m_data;
};
