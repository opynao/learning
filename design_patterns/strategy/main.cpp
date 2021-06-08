#include "car.h"

int main()
{
    auto spCar = std::make_shared<Crossover>(std::make_shared<GenericBrakeStrategy>(3),
                                             std::make_shared<GenericBeepStrategy>(10),
                                             std::make_shared<AutomaticTransmissionStrategy>());
    spCar->performBrake();
    spCar->performBeep();
    spCar->showTransmission();
    spCar->changeTransmission();
    spCar->setBrakeBehavior(std::make_shared<EmergencyBrakeStrategy>(9));
    spCar->changeTransmission();
    spCar->performBrake();

    return 0;
}
