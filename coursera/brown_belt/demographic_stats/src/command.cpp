#include "command.h"
#include "people.h"
#include <algorithm>

CommandHandler::CommandHandler(std::istream &is, std::ostream &os)
{
    const PeopleStats people(ReadPeople(is));
    for (std::string command; is >> command;)
    {
        auto itCommand = commands.find(command);
        if (itCommand != commands.cend())
            (this->*itCommand->second)(people, is, os);
    }
}

void CommandHandler::CommandAge(const PeopleStats &people, std::istream &is, std::ostream &os) const
{
    size_t adult_age;
    is >> adult_age;
    os << "There are " << people.GetAdultPeopleOlderThanAge(adult_age);
    os << " adult people for maturity age " << adult_age << '\n';
}

void CommandHandler::CommandWealthy(const PeopleStats &people, std::istream &is, std::ostream &os) const
{
    size_t count;
    is >> count;
    os << "Top-" << count << " people have total income ";
    os << people.GetPeopleWithTotalIncome(count) << '\n';
}

void CommandHandler::CommandPopularName(const PeopleStats &people, std::istream &is, std::ostream &os) const
{
    char gender;
    is >> gender;
    auto name = people.GetMostPopularName(gender);
    if (!name)
        os << "No people of gender " << gender << '\n';
    else
        os << "Most popular name among people of gender " << gender << " is " << name.value() << '\n';
}