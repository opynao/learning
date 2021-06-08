#include "statistics.h"

void StatisticsDisplay::Update(const double temperature, [[maybe_unused]] const double humidity, [[maybe_unused]] double pressure)
{
    m_temperatureStats.insert(temperature);
    Display(std::cout);
}

void StatisticsDisplay::Display(std::ostream &os) const
{
    os << "Average temperature is " << CalculateAverageTemp() << std::endl;
    os << "Minimum temperature is " << *m_temperatureStats.begin() << std::endl;
    os << "Maximum temperature is " << *m_temperatureStats.rbegin() << std::endl;
}

double StatisticsDisplay::CalculateAverageTemp() const
{
    return std::accumulate(m_temperatureStats.begin(), m_temperatureStats.end(), 0) / (1.0 * m_temperatureStats.size());
}
