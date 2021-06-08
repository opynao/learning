#pragma once

#include "observer.h"
#include "display.h"
#include "weather_data.h"

#include <set>
#include <numeric>
#include <memory>

class StatisticsDisplay : public IObserver,
                          public IDisplay,
                          public std::enable_shared_from_this<StatisticsDisplay>
{
public:
    void Update(const double temperature, [[maybe_unused]] const double humidity, [[maybe_unused]] double pressure) override;

private:
    void Display(std::ostream &os) const override;

    double CalculateAverageTemp() const;

private:
    std::multiset<double> m_temperatureStats;
};
