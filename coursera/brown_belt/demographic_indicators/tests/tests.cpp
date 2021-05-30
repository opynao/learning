#include "gtest/gtest.h"
#include "person.h"
#include "print_stats.h"

TEST(Basic, Test1)
{
    std::vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    std::string result{"Median age = 40\n"
                       "Median age for females = 40\n"
                       "Median age for males = 55\n"
                       "Median age for employed females = 40\n"
                       "Median age for unemployed females = 80\n"
                       "Median age for employed males = 55\n"
                       "Median age for unemployed males = 78\n"};
    EXPECT_EQ(PrintStats(persons).str(), result);
}