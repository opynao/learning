#pragma once

#include <string>

class Bus
{
public:
    Bus(const std::string &busName)
        : m_busName{busName}
    {
    }
    std::string GetBusName() const
    {
        return m_busName;
    }
    bool operator==(const Bus &bus) const
    {
        return m_busName == bus.GetBusName();
    }
    bool operator<(const Bus &bus) const
    {
        return m_busName < bus.GetBusName();
    }

private:
    std::string m_busName;
};