#pragma once
#include <iostream>

class IBeepStrategy
{
public:
    IBeepStrategy(int volume)
        : m_volume{volume}
    {
    }
    virtual ~IBeepStrategy() = default;
    virtual void beep() const = 0;

protected:
    int m_volume;
};

class GenericBeepStrategy : public IBeepStrategy
{
public:
    using IBeepStrategy::IBeepStrategy;

    void beep() const override
    {
        std::cout << "Be-Beeep with volume " << m_volume << " Hz" << std::endl;
    }
};

class UnusualBeepStrategy : public IBeepStrategy
{
public:
    using IBeepStrategy::IBeepStrategy;

    void beep() const override
    {
        std::cout << "Be-Be-Be-Beeeeeep with volume " << m_volume << " Hz" << std::endl;
    }
};