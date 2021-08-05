#pragma once
#include "base_validator.h"

#include <vector>
#include <algorithm>
#include <iostream>

bool in_vector(const std::string &value, const std::vector<std::string> &v)
{
    return std::find(v.begin(), v.end(), value) != v.end();
}

class HistoryValidator : public BaseValidator
{
private:
    std::vector<std::string> historyItems;

public:
    HistoryValidator(std::vector<std::string> historyItems) : historyItems(historyItems){};

    std::string validate(const std::string &testString) override
    {
        std::cout << "Checking if string is in history...\n";

        if (in_vector(testString, historyItems))
            return "Please enter a value that you haven't entered before";

        return BaseValidator::validate(testString);
    }
};