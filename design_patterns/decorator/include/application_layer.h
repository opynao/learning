#pragma once
#include "tcp_ip_decorator.h"

class ApplicationLayer : public TcpIpPacketDecorator
{
public:
    ApplicationLayer(const std::shared_ptr<IPacket> data)
        : TcpIpPacketDecorator(data)
    {
    }
    std::string GetData() const override
    {
        return m_data->GetData() + "\nsize : " + std::to_string(m_data->GetSize());
    }
    size_t GetSize() const override
    {
        return GetData().size();
    }
};