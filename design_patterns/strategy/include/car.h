#pragma once
#include "brake_strategy.h"
#include "beep_strategy.h"
#include "transmission_strategy.h"

#include <memory>
#include <string>

// template < typename Vehicle >
// class BrackeSystem
// {
// public:
//     BrackeSystem(Vehicle const &vehicle, std::vector<IBrakeStrategy&>)
//     {
//         vihicle.Subscribe( std::shared_from_this() );
//     }

//     void EmergyLevel( emergyLevel const level )
//     {
//         indexes = 1...m_vStrategies.size();
//         auto index = std::lower_bound(indexes, level);
//         m_rCurrentStrategy = m_vStrategies[index];
//     }

//     void Brake()
//     {
//         m_rCurrentStrategy->Break();
//     }

// private:
//     IBrakeStrategy &m_rCurrenStrategy;
//     std::vector<IBrakeStrategy&> m_vStrategies;

// };

class ICar
{
public:
    ICar(const std::shared_ptr<IBrakeStrategy> spBrakeStrategy,
         const std::shared_ptr<IBeepStrategy> spBeepStrategy,
         const std::shared_ptr<ITransmissionStrategy> spTransmissionStrategy)
        : m_spBrakeStrategy{spBrakeStrategy},
          m_spBeepStrategy{spBeepStrategy},
          m_spTransmissionStrategy{spTransmissionStrategy}
    {
    }

    virtual ~ICar()
    {
    }

    virtual void move() const
    {
        std::cout << "The car is moving" << std::endl;
    }

    void performBrake() const
    {
        m_spBrakeStrategy->brake();
    }

    void performBeep() const
    {
        m_spBeepStrategy->beep();
    }

    void showTransmission() const
    {
        m_spTransmissionStrategy->show();
    }

    void changeTransmission() const
    {
        m_spTransmissionStrategy->changeGear();
    }

    void setBrakeBehavior(const std::shared_ptr<IBrakeStrategy> brakeType)
    {
        m_spBrakeStrategy = brakeType;
    }

protected:
    std::shared_ptr<IBrakeStrategy> m_spBrakeStrategy;
    std::shared_ptr<IBeepStrategy> m_spBeepStrategy;
    std::shared_ptr<ITransmissionStrategy> m_spTransmissionStrategy;
};

class Crossover : public ICar
{
public:
    Crossover(const std::shared_ptr<IBrakeStrategy> spBrakeStrategy,
              const std::shared_ptr<IBeepStrategy> spBeepStrategy,
              const std::shared_ptr<ITransmissionStrategy> spTransmissionStrategy)
        : ICar(spBrakeStrategy, spBeepStrategy, spTransmissionStrategy)
    {
        std::cout << "Crossover" << std::endl;
    }

    using ICar::ICar;

    void move() const override
    {
        std::cout << "The crossover is moving" << std::endl;
    }
};

class HatchBack : public ICar
{
public:
    HatchBack(const std::shared_ptr<IBrakeStrategy> spBrakeStrategy,
              const std::shared_ptr<IBeepStrategy> spBeepStrategy,
              const std::shared_ptr<ITransmissionStrategy> spTransmissionStrategy)
        : ICar(spBrakeStrategy, spBeepStrategy, spTransmissionStrategy)
    {
        std::cout << "Hatchback" << std::endl;
    }

    using ICar::ICar;

    void move() const override
    {
        std::cout << "The hatchback is moving" << std::endl;
    }
};

class Minivan : public ICar
{
public:
    Minivan(const std::shared_ptr<IBrakeStrategy> spBrakeStrategy,
            const std::shared_ptr<IBeepStrategy> spBeepStrategy,
            const std::shared_ptr<ITransmissionStrategy> spTransmissionStrategy)
        : ICar(spBrakeStrategy, spBeepStrategy, spTransmissionStrategy)
    {
        std::cout << "Minivan" << std::endl;
    }

    void move() const override
    {
        std::cout << "The minivan is moving" << std::endl;
    }
};
