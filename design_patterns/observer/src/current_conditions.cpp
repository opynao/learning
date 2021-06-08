#include "current_conditions.h"

void CurrentConditionsDisplay::Update(const double temperature, const double humidity, const double pressure)
{
    m_temperature = temperature;
    m_humidity = humidity;
    m_pressure = pressure;
    Display(std::cout);
}

void CurrentConditionsDisplay::Display(std::ostream &os) const
{
    os << "Current temperature is " << m_temperature << std::endl;
    os << "Current humidity is " << m_humidity << std::endl;
    os << "Current pressure is " << m_pressure << std::endl;
}