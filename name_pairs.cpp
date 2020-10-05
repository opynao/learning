#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#define LOGF std::cerr << __FUNCTION__ << std::endl


class Name_pairs
{
public:
	using Name_t = std::string;
	using Age_t = double;
	size_t NamesSize {};
	explicit Name_pairs(size_t nameSize)
	{
		NamesSize = nameSize;
		names.reserve(NamesSize);
		ages.reserve(NamesSize);
	}
private:
  std::vector<Name_t> names;
  std::vector<Age_t> ages;
public:
  void read_ages()
  {
	LOGF;
	Age_t StudentAge {};
	for(size_t i = 0; i < NamesSize; ++i)
	{
		std::cout << "For name " << names[i] << " please, enter age" << std::endl;
		std::cin >> StudentAge;
		ages.push_back(StudentAge);
	}
	//std::copy(std::istream_iterator<Age_t>(std::cin),std::istream_iterator<Age_t>(),std::back_inserter(ages));
  }
  void read_names()
  {
	LOGF;
	for(size_t i = 0; i < NamesSize; ++i)
	{
		Name_t StudentName {};
		std::cin >> StudentName;
		names.push_back(StudentName);
	}
	//std::copy(std::istream_iterator<Name_t>(std::cin),std::istream_iterator<Name_t>(),std::back_inserter(names));
  }
  void print()
  {
	  LOGF;
	  for(size_t i = 0; i != names.size(); ++i)
	  {
		  print_name_and_age(i);
	  }
  }
private:
  void print_name_and_age(const size_t index)
  {
	std::cout << names[index] << " " << ages[index] << std::endl;
  }
 public:
  void sort()
  {
	std::vector<Name_t> namesCopy = names;
	std::vector<Age_t> agesCopy(NamesSize, 0);
	std::sort(names.begin(), names.end());
	auto findPosInSortedVectorAndMoveCorrespondingAgeToNewVectorOfAges = [this,&namesCopy,&agesCopy](const Name_t& name) 
	{
		const auto it = std::find(names.cbegin(),names.cend(),name);
		const auto it1 = std::find(namesCopy.cbegin(), namesCopy.cend(), name);
		const auto posOld = std::distance(namesCopy.cbegin(),it1);
		const auto posNew = std::distance(names.cbegin(),it);
		agesCopy[posNew] = ages[posOld];
	};
	std::for_each(namesCopy.cbegin(),namesCopy.cend(), findPosInSortedVectorAndMoveCorrespondingAgeToNewVectorOfAges);
	ages = agesCopy;
  }
};

/*void operator << (Name_pairs Student)
{
  for (int i = 0; i < Student.name.size(); i++)
  {
    std::cout << Student.name[i] << " " << Student.age[i] << std::endl;
  }
}

bool operator == (Name_pairs Student1, Name_pairs Student2)
{
  if (Student1.name == Student2.name && Student1.age == Student2.age)
    return true;
  else
    return false;
}

bool operator != (Name_pairs Student1, Name_pairs Student2)
{
  if (Student1.name != Student2.name && Student1.age != Student2.age)
    return true;
  else
    return false;
}
*/
int main()
{
  Name_pairs Students(3);
  Students.read_names();
  Students.read_ages();
  Students.print();
  Students.sort();
  Students.print();
  return 0;
}
