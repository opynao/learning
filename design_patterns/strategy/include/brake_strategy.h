#pragma once
#include <iostream>

class IBrakeStrategy
{
public:
    IBrakeStrategy(int brakeStrength)
        : m_brakeStrength{brakeStrength}
    {
    }
    virtual ~IBrakeStrategy() = default;
    virtual void brake() const = 0;

protected:
    int m_brakeStrength;
};

class GenericBrakeStrategy : public IBrakeStrategy
{
public:
    using IBrakeStrategy::IBrakeStrategy;

    void brake() const override
    {
        std::cout << "Generic brake strategy with strength " << m_brakeStrength << " out of 10 " << std::endl;
    }
};

class UrgentBrakeStrategy : public IBrakeStrategy
{
public:
    using IBrakeStrategy::IBrakeStrategy;

    void brake() const override
    {
        std::cout << "Urgent brake strategy with strength " << m_brakeStrength << " out of 10 " << std::endl;
    }
};

class EmergencyBrakeStrategy : public IBrakeStrategy
{
public:
    using IBrakeStrategy::IBrakeStrategy;

    void brake() const override
    {
        std::cout << "Emergency brake strategy with strength " << m_brakeStrength << " out of 10 " << std::endl;
    }
};