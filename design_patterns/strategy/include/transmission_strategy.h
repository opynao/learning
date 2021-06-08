#pragma once
#include <iostream>
#include <memory>
#include <array>
#include <vector>

class ITransmissionStrategy
{
public:
    virtual ~ITransmissionStrategy() = default;
    virtual void show() const = 0;
    virtual void changeGear() = 0;

protected:
    int m_volume;
};

class AutomaticTransmissionStrategy : public ITransmissionStrategy
{
public:
    void show() const override
    {
        std::cout << "You use automatic transmission" << std::endl;
    }
    void changeGear() override
    {
        if (m_currentPosition < gearPosition.size() - 1)
            ++m_currentPosition;
        else
            m_currentPosition -= (gearPosition.size() - 1);
        std::cout << "Your current gear is " << gearPosition[m_currentPosition] << std::endl;
    }

private:
    std::vector<std::string> gearPosition{
        "DRIVE",
        "PARK",
        "REVERSE",
        "NEUTRAL"};

private:
    size_t m_currentPosition{};
};

class ManualTransmissionStrategy : public ITransmissionStrategy
{
public:
    void show() const override
    {
        std::cout << "You use manual transmission" << std::endl;
    }
    void changeGear() override
    {
        if (m_currentPosition < MAX_GEAR_POSITION - 1)
            ++m_currentPosition;
        else
            m_currentPosition -= (MAX_GEAR_POSITION - 1);
        std::cout << "Your current gear is " << m_currentPosition << std::endl;
    }

private:
    int MAX_GEAR_POSITION = 5;
    int m_currentPosition{};
};