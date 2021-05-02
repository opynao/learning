#pragma once
#include <string>
#include <vector>
#include <istream>
#include <set>

using peopleStats_t = std::vector<Person>;

struct Person
{
    Person() = default;
    Person(int age_)
        : age{age_}
    {
    }
    std::string name;
    int age;
    int income;
    bool is_male;
    bool operator<(const Person &person) const
    {
        return age < person.age;
    }
};

peopleStats_t ReadPeople(std::istream &input);