#pragma once
#include "packet.h"
#include <memory>
#include <algorithm>

class PacketCryptoDecorator : public IPacket
{
public:
    PacketCryptoDecorator(std::shared_ptr<IPacket> data)
        : m_spData{std::move(data)}
    {
    }
    std::string GetData() const final
    {
        auto data = m_spData->GetData();
        std::transform(data.begin(), data.end(), data.begin(), [](const char ch)
                       { return ch + 1; });
        return data;
    }
    size_t GetSize() const final
    {
        return m_spData->GetSize();
    }

private:
    std::shared_ptr<IPacket> m_spData;
};