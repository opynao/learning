#pragma once

#include "interface_element.h"

class TextBox : public InterfaceElement
{
    std::string textValue = "";

public:
    using InterfaceElement::InterfaceElement;

    virtual void changeText(const std::string &newValue)
    {
        textValue = newValue;
        if (newValue.empty())
            m_spMediator->mediate(name + " is empty");

        else
            m_spMediator->mediate(name + " is not empty");
    }
};
