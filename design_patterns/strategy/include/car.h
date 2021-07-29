#pragma once
#include "brake_strategy.h"
#include "beep_strategy.h"
#include "transmission_strategy.h"

#include <memory>
#include <string>

class ICar
{
public:
    ICar(const std::shared_ptr<IBrakeStrategy> spBrakeStrategy,
         const std::shared_ptr<IBeepStrategy> spBeepStrategy,
         const std::shared_ptr<ITransmissionStrategy> spTransmissionStrategy);

    virtual ~ICar() = default;

    virtual void move() const;

    void performBrake() const;

    void performBeep() const;

    void showTransmission() const;

    void changeTransmission() const;

    void setBrakeBehavior(const std::shared_ptr<IBrakeStrategy> brakeType);

protected:
    std::shared_ptr<IBrakeStrategy> m_spBrakeStrategy;
    std::shared_ptr<IBeepStrategy> m_spBeepStrategy;
    std::shared_ptr<ITransmissionStrategy> m_spTransmissionStrategy;
};