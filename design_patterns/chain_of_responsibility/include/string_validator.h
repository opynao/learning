#pragma once
#include <string>
#include <memory>

class StringValidator
{
public:
    virtual std::shared_ptr<StringValidator> setNext(const std::shared_ptr<StringValidator> &nextValidator) = 0;
    virtual ~StringValidator() = default;
    virtual std::string validate(const std::string &) = 0;
};
