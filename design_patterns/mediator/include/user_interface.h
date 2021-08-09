#pragma once

#include "mediator.h"
#include "text_box.h"
#include "check_box.h"
#include "button_element.h"

#include <iostream>
#include <memory>

class UserInterface : public Mediator
{
public:
    UserInterface(const std::shared_ptr<TextBox> &nameTextBox,
                  const std::shared_ptr<CheckBox> &isMarriedCheckbox,
                  const std::shared_ptr<TextBox> &spousesNameTextBox,
                  const std::shared_ptr<ButtonElement> &submitButton,
                  const std::shared_ptr<TextBox> &ageTextBox)
        : m_nameTextBox(nameTextBox),
          m_isMarriedCheckbox(isMarriedCheckbox),
          m_spousesNameTextBox(spousesNameTextBox),
          m_submitButton(submitButton),
          m_ageTextBox(ageTextBox)
    {
    }
    void mediate(const std::string &event) override
    {
        std::cout << "Mediating event: " << event << "...\n";

        if (event == "Name textbox is empty")
        {
            m_submitButton->setVisibility(Visibility::Hidden);
        }
        else if (event == "Name textbox is not empty")
        {
            m_submitButton->setVisibility(Visibility::Visible);
        }
        else if (event == "Age textbox is empty")
        {
            m_submitButton->setVisibility(Visibility::Hidden);
        }
        else if (event == "Age textbox is not empty")
        {
            m_submitButton->setVisibility(Visibility::Visible);
        }
        else if (event == "Is married checkbox is checked")
        {
            m_spousesNameTextBox->setVisibility(Visibility::Visible);
        }
        else if (event == "Is married checkbox is unchecked")
        {
            m_spousesNameTextBox->setVisibility(Visibility::Hidden);
        }
        else if (event == "Submit button clicked")
        {
            std::cout << "Submitted!\n";
        }
        else
        {
            std::cout << "Unrecognized event!";
        }
    }
    std::shared_ptr<TextBox> getNameTextBox() const
    {
        return m_nameTextBox;
    };
    std::shared_ptr<CheckBox> getIsMarriedCheckbox() const
    {
        return m_isMarriedCheckbox;
    };
    std::shared_ptr<TextBox> getSpousesNameTextBox() const
    {
        return m_spousesNameTextBox;
    };
    std::shared_ptr<ButtonElement> getSubmitButton() const
    {
        return m_submitButton;
    };
    std::shared_ptr<TextBox> getAgeTextBox() const
    {
        return m_ageTextBox;
    }

private:
    std::shared_ptr<TextBox> m_nameTextBox;
    std::shared_ptr<CheckBox> m_isMarriedCheckbox;
    std::shared_ptr<TextBox> m_spousesNameTextBox;
    std::shared_ptr<ButtonElement> m_submitButton;
    std::shared_ptr<TextBox> m_ageTextBox;
};
