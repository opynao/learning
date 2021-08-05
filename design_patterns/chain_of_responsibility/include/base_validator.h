#pragma once
#include "string_validator.h"

class BaseValidator : public StringValidator
{
protected:
    std::shared_ptr<StringValidator> next = nullptr;

public:
    ~BaseValidator() = default;

    std::shared_ptr<StringValidator> setNext(
        const std::shared_ptr<StringValidator> &nextValidator) override
    {
        next = nextValidator;
        return nextValidator;
    }

    virtual std::string validate(const std::string &testString) override
    {
        if (this->next)
        {
            return this->next->validate(testString);
        }
        return "Success!";
    }
};
