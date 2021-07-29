#include "car.h"

ICar::ICar(const std::shared_ptr<IBrakeStrategy> spBrakeStrategy,
           const std::shared_ptr<IBeepStrategy> spBeepStrategy,
           const std::shared_ptr<ITransmissionStrategy> spTransmissionStrategy)
    : m_spBrakeStrategy{spBrakeStrategy},
      m_spBeepStrategy{spBeepStrategy},
      m_spTransmissionStrategy{spTransmissionStrategy}
{
}

void ICar::move() const
{
    std::cout << "The car is moving" << std::endl;
}

void ICar::performBrake() const
{
    m_spBrakeStrategy->brake();
}

void ICar::performBeep() const
{
    m_spBeepStrategy->beep();
}

void ICar::showTransmission() const
{
    m_spTransmissionStrategy->show();
}

void ICar::changeTransmission() const
{
    m_spTransmissionStrategy->changeGear();
}

void ICar::setBrakeBehavior(const std::shared_ptr<IBrakeStrategy> brakeType)
{
    m_spBrakeStrategy = brakeType;
}