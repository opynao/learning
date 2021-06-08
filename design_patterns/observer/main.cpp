#include "weather_data.h"
#include "current_conditions.h"
#include "statistics.h"
#include "forecast.h"

int main()
{
    auto currentConditionsDisplay = std::make_shared<CurrentConditionsDisplay>();
    auto statisticsDisplay = std::make_shared<StatisticsDisplay>();
    auto forecastDisplay = std::make_shared<ForecastDisplay>();

    WeatherData weatherData;

    weatherData.Add(currentConditionsDisplay);
    weatherData.Add(statisticsDisplay);
    weatherData.Add(forecastDisplay);

    weatherData.setMeasurements(22.1, 83.2, 761.1);
    weatherData.setMeasurements(19.0, 79.0, 759.8);
    return 0;
}