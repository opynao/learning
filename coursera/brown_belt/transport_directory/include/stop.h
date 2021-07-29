#pragma once
#include <string>

class Stop
{
public:
    Stop() = default;
    Stop(const std::string &stopName)
        : m_stopName{stopName}
    {
    }
    std::string GetStopName() const
    {
        return m_stopName;
    }
    bool operator==(const Stop &other) const
    {
        return m_stopName == other.GetStopName();
    }
    bool operator<(const Stop &other) const
    {
        return m_stopName < other.GetStopName();
    }
private:
    std::string m_stopName;
};