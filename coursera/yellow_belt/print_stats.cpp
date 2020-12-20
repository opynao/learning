#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
/*
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

enum class Gender 
{
	FEMALE,
	MALE
};


struct Person 
{
	int age;  // возраст
	Gender gender;  // пол
	bool is_employed;  // имеет ли работу
};


template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) 
{
	if (range_begin == range_end) 
	{
		return 0;
	}
	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element( begin(range_copy), middle, end(range_copy),
	[](const Person& lhs, const Person& rhs) { return lhs.age < rhs.age; } );
	return middle->age;
}
*/

void PrintStats(vector<Person> persons)
{
	int MA = ComputeMedianAge(persons.begin(), persons.end());
	std::cout << "Median age = " << MA << std::endl;
	
	std::vector<Person> females {persons};
	auto it = std::partition(females.begin(), females.end(), [](Person ps){return ps.gender == Gender::FEMALE;});
	females.erase(it, females.end());
	MA = ComputeMedianAge(females.begin(), females.end());
	std::cout << "Median age for females = " << MA << std::endl;

	std::vector<Person> males {persons};
	it = std::partition(males.begin(), males.end(), [](Person ps){return ps.gender == Gender::MALE;});
	males.erase(it, males.end());
	MA = ComputeMedianAge(males.begin(), males.end());
	std::cout << "Median age for males = " << MA << std::endl;

	std::vector<Person> employed_females {persons};
	it = std::partition(employed_females.begin(), employed_females.end(), [](Person ps){return (ps.gender == Gender::FEMALE && ps.is_employed == true);});
	employed_females.erase(it, employed_females.end());
	MA = ComputeMedianAge(employed_females.begin(), employed_females.end());
	std::cout << "Median age for employed females = " << MA << std::endl;

	std::vector<Person> unemployed_females {persons};
	it = std::partition(unemployed_females.begin(), unemployed_females.end(), [](Person ps){return (ps.gender == Gender::FEMALE && ps.is_employed == false);});
	unemployed_females.erase(it, unemployed_females.end());
	MA = ComputeMedianAge(unemployed_females.begin(), unemployed_females.end());
	std::cout << "Median age for unemployed females = " << MA << std::endl;

	std::vector<Person> employed_males {persons};
	it = std::partition(employed_males.begin(), employed_males.end(), [](Person ps){return (ps.gender == Gender::MALE && ps.is_employed == true);});
	employed_males.erase(it, employed_males.end());
	MA = ComputeMedianAge(employed_males.begin(), employed_males.end());
	std::cout << "Median age for employed males = " << MA << std::endl;

	std::vector<Person> unemployed_males {persons};
	it = std::partition(unemployed_males.begin(), unemployed_males.end(), [](Person ps){return (ps.gender == Gender::MALE && ps.is_employed == false);});
	unemployed_males.erase(it, unemployed_males.end());
	MA = ComputeMedianAge(unemployed_males.begin(), unemployed_males.end());
	std::cout << "Median age for unemployed males = " << MA << std::endl;

}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}

