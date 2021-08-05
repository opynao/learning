#include "base_validator.h"
#include <iostream>

class NotEmptyValidator : public BaseValidator
{
public:
    std::string validate(const std::string& testString) override
    {
        std::cout << "Checking if empty...\n";

        if (testString.empty())
        {
            return "Please enter a value";
        }

        return BaseValidator::validate(testString);
    }
};
