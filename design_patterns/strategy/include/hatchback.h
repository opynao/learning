#pragma
#include "car.h"

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

    void move() const override
    {
        std::cout << "The hatchback is moving" << std::endl;
    }
};