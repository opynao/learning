#include "user_interface.h"

#include <memory>
#include <vector>
#include <algorithm>

void printCurrentInformation(const std::vector<std::shared_ptr<InterfaceElement>> &elements)
{
    std::cout << "-------------------"
              << "\n";
    for (const auto &element : elements)
    {
        std::cout << element->getDescription() << "\n";
    }
    std::cout << "-------------------"
              << "\n";
}

int main()
{
    auto nameTextBox = std::make_shared<TextBox>("Name textbox", Visibility::Visible);
    auto isMarriedCheckbox = std::make_shared<CheckBox>("Is married checkbox", Visibility::Visible);
    auto spousesNameTextBox = std::make_shared<TextBox>("Spouse's name textbox", Visibility::Hidden);
    auto submitButton = std::make_shared<ButtonElement>("Submit button", Visibility::Hidden);
    auto ageTextBox = std::make_shared<TextBox>("Age textbox", Visibility::Visible);

    auto ui = std::make_shared<UserInterface>(nameTextBox, isMarriedCheckbox, spousesNameTextBox, submitButton, ageTextBox);

    std::vector<std::shared_ptr<InterfaceElement>> elements = {
        ui->getNameTextBox(),
        ui->getAgeTextBox(),
        ui->getIsMarriedCheckbox(),
        ui->getSpousesNameTextBox(),
        ui->getSubmitButton()};

    std::for_each(elements.begin(), elements.end(), [&ui](std::shared_ptr<InterfaceElement> &element)
                  { element->setMediator(ui); });

    printCurrentInformation(elements);

    ui->getNameTextBox()->changeText("vika");
    ui->getAgeTextBox()->changeText("20.07.1996");
    ui->getIsMarriedCheckbox()->setIsChecked(true);

    printCurrentInformation(elements);

    ui->getSubmitButton()->click();

    printCurrentInformation(elements);

    return 0;
}
