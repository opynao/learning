#pragma once

#include "interface_element.h"

class CheckBox : public InterfaceElement
{
public:
    using InterfaceElement::InterfaceElement;

    void setIsChecked(bool isCheck)
    {
        this->isChecked = isCheck;

        if (isCheck)
            m_spMediator->mediate(name + " is checked");

        else
            m_spMediator->mediate(name + " is unchecked");
    }

private:
    bool isChecked = false;
};
