#pragma once

#include "mediator.h"

#include <memory>

enum class Visibility
{
    Visible,
    Hidden
};

class InterfaceElement
{
public:
    InterfaceElement(const std::string &name, const Visibility isVisible)
        : name(name),
          isVisible(isVisible)
    {
    }
    virtual ~InterfaceElement() = default;

    void setMediator(const std::shared_ptr<Mediator> &mediator)
    {
        m_spMediator = mediator;
    }

    void setVisibility(const Visibility isVis)
    {
        isVisible = isVis;
    }

    std::string getDescription() const
    {
        return isVisible == Visibility::Visible ? name + " is visible"
                                                : name + " is NOT visible";
    }

protected:
    std::string name;
    Visibility isVisible{Visibility::Visible};
    std::shared_ptr<Mediator> m_spMediator;
};
