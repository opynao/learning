#pragma once
#include "stop.h"
#include "coordinate.h"

#include <vector>
#include <algorithm>
#include <map>

class StopsMap
{
public:
    bool IsEmpty() const
    {
        return m_stops.empty();
    }
    size_t Size() const
    {
        return m_stops.size();
    }
    void Add(const Stop &stop, const Coordinate &coordinate)
    {
        m_stops.emplace(stop, coordinate);
    }
    bool Has(const Stop &stop)
    {
        return m_stops.find(stop) != m_stops.cend();
    }

private:
    std::map<Stop, Coordinate> m_stops;
};