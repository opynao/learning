#include "base_validator.h"

#include <regex>
#include <iostream>

class RegexValidator : public BaseValidator
{
private:
    std::string m_patternName;
    std::string m_regexString;

public:
    RegexValidator(const std::string &patternName, const std::string &regexString)
        : m_patternName(patternName), m_regexString(regexString)
    {
    }

    std::string validate(const std::string &testString) override
    {
        std::cout << "Checking if string is a valid " << m_patternName << "...\n";

        if (!std::regex_match(testString, std::regex(m_regexString)))
        {
            return "The value entered is not a valid " + m_patternName;
        }

        return BaseValidator::validate(testString);
    }
};
