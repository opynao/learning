#include "base_validator.h"

#include <iostream>
#include <algorithm>
#include <cctype>

class NumberValidator : public BaseValidator
{
public:
    std::string validate(const std::string &testString) override
    {
        std::cout << "Checking if string contains numbers ...\n";

        bool containNumbers{false};
        std::for_each(testString.cbegin(), testString.cend(),
                      [&containNumbers](const char ch)
                      {
                          if (std::isdigit(ch))
                              containNumbers = true;
                      });
        if (!containNumbers)
        {
            return "Please enter a string with numbers ";
        }
        return BaseValidator::validate(testString);
    }
};