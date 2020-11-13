#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
/*
enum class Language 
{
	DE,
	FR,
	IT
};


struct Region
{
	std::string std_name;
	std::string parent_std_name;
	std::map<Language, std::string> names;
	int64_t population;
};
*/
bool operator==(const Region& lhs,const Region& rhs)
{
	return (lhs.std_name == rhs.std_name && lhs.parent_std_name == rhs.parent_std_name && lhs.names == rhs.names && lhs.population == rhs.population);
}


size_t FindMaxRepetitionCount(const std::vector<Region>& vRegions)
{
	if(vRegions.size() == 0)
		return 0;
	
	std::set<size_t> sNumberOfElems {};
	std::vector<Region> vReg {};

	std::for_each(vRegions.cbegin(),vRegions.cend(), [&sNumberOfElems,&vRegions,&vReg](const auto& region)
			{
				auto it = std::find(vReg.cbegin(),vReg.cend(),region);
				if(it != vReg.cend())
					return;

				size_t numberOfRepetition = std::count(vRegions.cbegin(),vRegions.cend(),region);
 				sNumberOfElems.insert(numberOfRepetition);
				vReg.push_back(region);
			}
		     );
	
	return *sNumberOfElems.rbegin();
}


int main() 
{
/*	
	std::vector<Region> vEmptyVector {};
	std::cout << FindMaxRepetitionCount(vEmptyVector) << std::endl;
	std::vector<Region> vRegions{
      {
          "Moscow",
          "Russia",
          {{Language::DE, "Moskau"}, {Language::FR, "Moscou"}, {Language::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Language::DE, "Russland"}, {Language::FR, "Russie"}, {Language::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Language::DE, "Moskau"}, {Language::FR, "Moscou"}, {Language::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Language::DE, "Moskau"}, {Language::FR, "Moscou"}, {Language::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Language::DE, "Russland"}, {Language::FR, "Russie"}, {Language::IT, "Russia"}},
          89
      },
  };
	std::cout << FindMaxRepetitionCount(vRegions) << std::endl;

	std::vector<Region> vReg{
      {
          "Moscow",
          "Russia",
          {{Language::DE, "Moskau"}, {Language::FR, "Moscou"}, {Language::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Language::DE, "Russland"}, {Language::FR, "Russie"}, {Language::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Language::DE, "Moskau"}, {Language::FR, "Moscou deux"}, {Language::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Language::DE, "Moskau"}, {Language::FR, "Moscou"}, {Language::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Language::DE, "Moskau"}, {Language::FR, "Moscou"}, {Language::IT, "Mosca"}},
          31
      },
  };
	
	std::cout << FindMaxRepetitionCount(vReg) << std::endl;
*/	
	return 0;
}

