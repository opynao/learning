#pragma once
#include "person.h"
#include "people.h"

#include <iostream>
#include <unordered_map>

class CommandHandler
{
public:
    typedef void (CommandHandler::*pFunc)(const PeopleStats &people, std::istream &is, std::ostream &os) const;
    using functionCall_t = std::unordered_map<std::string, pFunc>;

public:
    CommandHandler(std::istream &is, std::ostream &os);
    void CommandAge(const PeopleStats &people, std::istream &is, std::ostream &os) const;
    void CommandWealthy(const PeopleStats &people, std::istream &is, std::ostream &os) const;
    void CommandPopularName(const PeopleStats &people, std::istream &is, std::ostream &os) const;

private:
    functionCall_t commands{
        {"AGE", &CommandHandler::CommandAge},
        {"WEALTHY", &CommandHandler::CommandWealthy},
        {"POPULAR_NAME", &CommandHandler::CommandPopularName}};
};