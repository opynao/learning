#pragma once
#include "tcp_ip_decorator.h"

class IpLayer : public TcpIpPacketDecorator
{
public:
    IpLayer(const std::shared_ptr<IPacket> data)
        : TcpIpPacketDecorator(data)
    {
    }
    std::string GetData() const override
    {
        return m_data->GetData() + "\nprotocol: " + protocol + " version: " + version;
    }
    size_t GetSize() const override
    {
        return 1;
    }

private:
    std::string protocol{"ip"};
    std::string version{"1.0"};
};