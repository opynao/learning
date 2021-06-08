#pragma once
#include "observer.h"
#include "display.h"
#include "weather_data.h"

#include <memory>

class CurrentConditionsDisplay : public IObserver,
                                 public IDisplay,
                                 public std::enable_shared_from_this<IObserver>
{
public:
    void Update(const double temperature, const double humidity, const double pressure) override;

private:
    void Display(std::ostream &os) const override;

private:
    double m_temperature;
    double m_humidity;
    double m_pressure;
};