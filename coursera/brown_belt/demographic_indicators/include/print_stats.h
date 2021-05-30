#pragma once

#include "person.h"
#include "compute_median_age.h"
#include "printer.h"
#include "ranger.h"
#include "utils.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

std::ostringstream PrintStats(std::vector<Person> persons)
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

    return printer.Print();
}