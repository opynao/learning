#pragma once
#include "observer.h"
#include "display.h"
#include "weather_data.h"

#include <vector>

class ForecastDisplay : public IObserver,
                        public IDisplay,
                        public std::enable_shared_from_this<ForecastDisplay>
{
public:
    void Update(const double temperature, [[maybe_unused]] const double humidity, [[maybe_unused]] double pressure) override;

private:
    void Display(std::ostream &os) const override;

private:
    std::vector<double> m_temperatureStatistics;
};