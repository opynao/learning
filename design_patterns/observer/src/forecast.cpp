#include "forecast.h"

void ForecastDisplay::Update(const double temperature, [[maybe_unused]] const double humidity, [[maybe_unused]] double pressure)
{
    m_temperatureStatistics.push_back(temperature);
    Display(std::cout);
}

void ForecastDisplay::Display(std::ostream &os) const
{
    if (*m_temperatureStatistics.rbegin() > 20)
        os << "The weather will be fine" << std::endl;
    else
        os << "Sunny days are coming!" << std::endl;
}
