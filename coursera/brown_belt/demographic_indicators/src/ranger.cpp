#include "ranger.h"
#include "utils.h"

#include <algorithm>

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
