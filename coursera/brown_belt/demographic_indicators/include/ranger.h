#pragma once

#include "person.h"
#include "gender.h"

#include <vector>

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