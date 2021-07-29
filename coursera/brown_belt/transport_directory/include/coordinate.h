#pragma once

class Coordinate
{
public:
    Coordinate() = default;
    Coordinate(const double latitude, const double longitude)
        : m_latitude{latitude}, m_longitude{longitude}
    {
    }

private:
    double m_latitude;
    double m_longitude;
};