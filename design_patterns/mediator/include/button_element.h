#pragma once

#include "interface_element.h"

class ButtonElement : public InterfaceElement
{
public:
    using InterfaceElement::InterfaceElement;
    
    virtual void click()
    {
        m_spMediator->mediate(name + " clicked");
    };
};
