#pragma once
#include "base_validator.h"

#include <iostream>

class LengthValidator : public BaseValidator
{
private:
    int m_minLength;

public:
    LengthValidator(int minLength)
        : m_minLength(minLength)
    {
    }

    std::string validate(const std::string &testString) override
    {
        std::cout << "Checking if length equals " << m_minLength << "...\n";

        if (static_cast<int>(testString.size()) < m_minLength)
        {
            return "Please enter a value longer than " + std::to_string(m_minLength);
        }

        return BaseValidator::validate(testString);
    }
};