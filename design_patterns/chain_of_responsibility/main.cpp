#include "base_validator.h"
#include "not_empty_validator.h"
#include "regex_validator.h"
#include "length_validator.h"
#include "uppercase_validator.h"
#include "number_validator.h"

int main()
{
    auto emailValidator = std::make_shared<BaseValidator>();

    emailValidator->setNext(std::make_shared<NotEmptyValidator>())
        ->setNext(std::make_shared<LengthValidator>(5));

    std::cout << "Checking Emails ---------------\n";
    std::cout << "Input: \n"
              << emailValidator->validate("") << "\n\n";
    std::cout << "Input: shaun\n"
              << emailValidator->validate("shaun") << "\n\n";
    std::cout << "Input: shaun@test.com\n"
              << emailValidator->validate("shaun@test.com") << "\n\n";

    std::vector<std::string> oldPasswords = {"abc123", "123456", "hello", "Hello1"};
    auto passwordValidator = std::make_shared<BaseValidator>();

    passwordValidator->setNext(std::make_shared<NotEmptyValidator>())
        ->setNext(std::make_shared<LengthValidator>(5))
        ->setNext(std::make_shared<UpperCaseValidator>())
        ->setNext(std::make_shared<NumberValidator>());

    for (const auto &password : oldPasswords)
        std::cout << passwordValidator->validate(password);

    return 0;
}