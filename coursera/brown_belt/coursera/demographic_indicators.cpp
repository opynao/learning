#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

class Printer
{
public:
    void Push(const std::string &str, const int medianAge);

    void Print() const;

private:
    std::vector<std::pair<std::string, int>> m_info;
};

void Printer::Push(const std::string &str, const int medianAge)
{
    m_info.emplace_back(str, medianAge);
}

void Printer::Print() const
{
    std::ostringstream oss;
    for (const auto &info : m_info)
        std::cout << info.first << info.second << "\n";
}

class Ranger
{
public:
    using vPersonIt = std::vector<Person>::const_iterator;
    Ranger(const std::vector<Person> &persons);

    vPersonIt GetEndOfRange(const Gender &gender);

    vPersonIt GetEndOfRange(const Gender &gender, const bool is_employed);

    vPersonIt GetRangeBegin() const;

private:
    std::vector<Person> m_persons;
};

Ranger::Ranger(const std::vector<Person> &persons)
    : m_persons{persons}
{
}

Ranger::vPersonIt Ranger::GetEndOfRange(const Gender &gender)
{
    return std::partition(std::begin(m_persons), std::end(m_persons),
                          [&](const Person &person) { return person.gender == gender; });
}

Ranger::vPersonIt Ranger::GetEndOfRange(const Gender &gender, const bool is_employed)
{
    return std::partition(std::begin(m_persons), std::end(m_persons),
                          [&](const Person &person) { return person.gender == gender && person.is_employed == is_employed; });
}

Ranger::vPersonIt Ranger::GetRangeBegin() const
{
    return std::cbegin(m_persons);
}

void PrintStats(std::vector<Person> persons)
{
    Printer printer;
    Ranger ranger(persons);

    printer.Push("Median age = ", ComputeMedianAge(std::cbegin(persons), std::cend(persons)));

    printer.Push("Median age for females = ",
                 ComputeMedianAge(ranger.GetRangeBegin(), ranger.GetEndOfRange(Gender::FEMALE)));

    printer.Push("Median age for males = ",
                 ComputeMedianAge(ranger.GetRangeBegin(), ranger.GetEndOfRange(Gender::MALE)));

    printer.Push("Median age for employed females = ",
                 ComputeMedianAge(ranger.GetRangeBegin(), ranger.GetEndOfRange(Gender::FEMALE, true)));

    printer.Push("Median age for unemployed females = ",
                 ComputeMedianAge(ranger.GetRangeBegin(), ranger.GetEndOfRange(Gender::FEMALE, false)));

    printer.Push("Median age for employed males = ",
                 ComputeMedianAge(ranger.GetRangeBegin(), ranger.GetEndOfRange(Gender::MALE, true)));

    printer.Push("Median age for unemployed males = ",
                 ComputeMedianAge(ranger.GetRangeBegin(), ranger.GetEndOfRange(Gender::MALE, false)));

    printer.Print();
}