#pragma once
#include "car.h"

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

    void move() const override
    {
        std::cout << "The crossover is moving" << std::endl;
    }
};