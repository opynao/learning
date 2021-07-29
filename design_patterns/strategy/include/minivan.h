#pragma
#include "car.h"

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