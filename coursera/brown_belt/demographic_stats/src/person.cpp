#include "person.h"
#include <set>

peopleStats_t ReadPeople(std::istream &input)
{
    int count;
    input >> count;

    peopleStats_t result;
    for (int i = 0; i != count; ++i)
    {
        Person p;
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
        result.push_back(std::move(p));
    }

    return result;
}
