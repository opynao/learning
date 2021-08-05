#pragma once

#include "observer.h"
#include "publisher.h"
#include <iostream>

class WeatherData : public IPublisher
{
public:
    void setMeasurements(const double temperature, const double humidity, const double pressure)
    {
        m_temperature = temperature;
        m_humidity = humidity;
        m_pressure = pressure;
        measurementsChanged();
    }
    void setTemperature(const double temperature)
    {
        m_temperature = temperature;
        measurementsChanged();
    }
    void setHumidity(const double humidity)
    {
        m_humidity = humidity;
        measurementsChanged();
    }
    void setPressure(const double pressure)
    {
        m_pressure = pressure;
        measurementsChanged();
    }
    void measurementsChanged() const
    {
        Notify();
    }

private:
    void Notify() const override
    {
        for (const auto &observer : m_observers)
            observer->Update(m_temperature, m_humidity, m_pressure);
    }

private:
    double m_temperature{};
    double m_humidity{};
    double m_pressure{};
};
