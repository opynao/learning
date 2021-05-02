#pragma once

#include "person.h"
#include "iterator_range.h"

#include <functional>
#include <set>
#define PR(x) std::cerr << #x << " = " << x << std::endl
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

class PeopleStats
{
public:
    PeopleStats() = default;
    explicit PeopleStats(const peopleStats_t &people);
    size_t GetAdultPeopleOlderThanAge(const size_t adult_age) const;
    size_t GetPeopleWithTotalIncome(const size_t count) const;
    std::optional<std::string> GetMostPopularName(const char gender) const;
    std::optional<std::string> GetName(const std::multiset<std::string> &s) const;

private:
    std::multiset<Person> peopleSortByAge_;
    std::multiset<int> income_;
    std::multiset<std::string> male_;
    std::multiset<std::string> female_;

    mutable std::vector<size_t> incomeSum_;
    std::optional<std::string> mostPopularMaleName_;
    std::optional<std::string> mostPopularFemaleName_;

    struct Cache
    {
        size_t middleAge_;
        size_t middleNumberOfPeople_;
        std::multiset<Person>::iterator itMiddle_;
    };
    std::optional<Cache> cache_;
};