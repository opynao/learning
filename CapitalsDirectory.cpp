#include <memory>
#include <cassert>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using countryName_t = std::string;
using capitalName_t = std::string;
using commandName_t = std::string;
using mCountryCapital_t = std::map<countryName_t,capitalName_t>; 

void ChangeCapitalCommand(mCountryCapital_t&);
void AboutCommand(mCountryCapital_t&);
void DumpCommand(mCountryCapital_t&);
void RenameCommand(mCountryCapital_t&);

enum class Answers
{
	IntroduceNewCountry,
	CountryHasNotChangeCapital,
	CountryHasChangedCapital,
	CountryDoesNotExist,
	CountryHasCapital,
	Error
};

std::map<commandName_t,void(*)(mCountryCapital_t&)> mInputCases
{
	{"CHANGE_CAPITAL",&ChangeCapitalCommand},
	{"ABOUT",&AboutCommand},
	{"DUMP",&DumpCommand},
	{"RENAME",&RenameCommand}
};

struct Country
{
	Answers ChangeCapital(mCountryCapital_t&);
	countryName_t m_country {};
	capitalName_t m_capital {};
};

//-------------------------CHANGE-CAPITAL---------------------------------------------

void ChangeCapitalCommand(mCountryCapital_t& mCountriesCapitals)
{
	countryName_t countryName {};
	capitalName_t capitalName {};
	std::cin >> countryName >> capitalName;
	Country newCountry;
	newCountry.m_country = countryName;
	newCountry.m_capital = capitalName;

	const auto itTempCapital = mCountriesCapitals.find(countryName);
	capitalName_t oldCapital {};
	if(mCountriesCapitals.cend() != itTempCapital)
	{
		oldCapital = itTempCapital->second;
	}
	
	Answers	functionAnswer = newCountry.ChangeCapital(mCountriesCapitals);
	
	switch(functionAnswer)
	{
		case Answers::IntroduceNewCountry:
			std::cout << "Introduce new country " << countryName << " with capital " << capitalName << std::endl; 
			break;
		case Answers::CountryHasNotChangeCapital:
			std::cout << "Country " << countryName << " hasn't changed its capital" <<std::endl;
			break;
		case Answers::CountryHasChangedCapital:
			std::cout << "Country " << countryName << " has changed its capital from "<< oldCapital <<" to "<< capitalName <<std::endl;
			break;
		default:
			break;
	}
}

Answers Country::ChangeCapital(mCountryCapital_t& mCountriesCapitals)
{
	const auto itFindCountry = mCountriesCapitals.find(m_country); 
	if(mCountriesCapitals.cend() == itFindCountry)
	{
		mCountriesCapitals.emplace(m_country,m_capital);
		return Answers::IntroduceNewCountry;
	}
	else
	{
	       if(mCountriesCapitals[m_country] == m_capital)
		      return Answers::CountryHasNotChangeCapital;
	       else
	       {	
		       mCountriesCapitals[m_country] = m_capital;
		       return Answers::CountryHasChangedCapital;
	       }
	}
}

//--------------------ABOUT------------------------------------------------------------------

void AboutCommand(mCountryCapital_t& mCountriesCapitals)
{
	countryName_t countryName {};
	std::cin >> countryName;
	if(mCountriesCapitals.empty())
		std::cout << "Country " << countryName << " doesn't exist" << std::endl; 
	else
	{
		if(mCountriesCapitals.count(countryName))
			std::cout << "Country " << countryName << " has capital " << mCountriesCapitals[countryName] << std::endl;
		else 
			std::cout << "Country " << countryName << " doesn't exist" << std::endl; 
	}
}

//-------------------------DUMP---------------------------------------------------------------
void DumpCommand(mCountryCapital_t& mCountriesCapitals)
{
	if(mCountriesCapitals.empty())
		std::cout << "There are no countries in the world" << std::endl;
	else
	{
		using map_t = std::remove_reference<decltype(mCountriesCapitals)>::type;
		std::for_each(std::cbegin(mCountriesCapitals),std::cend(mCountriesCapitals),[](map_t::const_reference pr)
				{
					std::cout << pr.first << "/" << pr.second << " ";
				}
			     );
		std::cout << std::endl;
	}
}

//------------------------RENAME--------------------------------------------------------------

void RenameCommand(mCountryCapital_t& mCountriesCapitals)
{
	countryName_t oldCountryName {};
	countryName_t newCountryName {};
	std::cin >> oldCountryName >> newCountryName;
	auto itFindNewCountry = mCountriesCapitals.find(newCountryName);
	if(mCountriesCapitals.empty())
		std::cout << "Incorrect rename, skip" << std::endl; 
	else
	{	
		if(mCountriesCapitals.cend() != itFindNewCountry || mCountriesCapitals.count(oldCountryName) == 0)
			std::cout << "Incorrect rename, skip" << std::endl; 
		else
		{
			std::cout << "Country " << oldCountryName << " with capital " << mCountriesCapitals[oldCountryName] << " has been renamed to " << newCountryName << std::endl;
			mCountriesCapitals.emplace(newCountryName,mCountriesCapitals[oldCountryName]);
			mCountriesCapitals.erase(oldCountryName);
		}
	}
}

//-------------------CALLING-MODULE---------------------------------------------------

void CallingModule(mCountryCapital_t& mCountriesCapitals)
{
	std::string command {};
	std::cin >> command;
	auto itCall = mInputCases.find(command);
	if(mInputCases.cend() != itCall)
	{
		itCall->second(mCountriesCapitals);
	}
}

//---------------------------------------------------------------------------------

void testChangeCapital_IntroduceNewCountry()
{
	mCountryCapital_t mCountriesCapitals {};
	Country newCountry {"Russia","Moscow"};
	assert(Answers::IntroduceNewCountry == newCountry.ChangeCapital(mCountriesCapitals));
}

void testChangeCapital_CountryHasNotChangeCapital()
{
	mCountryCapital_t mCountriesCapitals {};
	mCountriesCapitals.emplace("Russia","Moscow");
	Country newCountry{"Russia","Moscow"};
	assert(Answers::CountryHasNotChangeCapital == newCountry.ChangeCapital(mCountriesCapitals));
}

void testChangeCapital_CountryHasChangedCapital()
{
	mCountryCapital_t mCountriesCapitals {};
	mCountriesCapitals.emplace("Russia","Moscow");
	Country newCountry{"Russia","London"};
	assert(Answers::CountryHasChangedCapital == newCountry.ChangeCapital(mCountriesCapitals));
}

int main()
{
	size_t NumberOfCalls {};
	std::cin >> NumberOfCalls;
	mCountryCapital_t mCountriesCapitals {};
	while(NumberOfCalls--)
	{
		CallingModule(mCountriesCapitals);
	}
//	testChangeCapital_IntroduceNewCountry();
//	testChangeCapital_CountryHasNotChangeCapital();
	return 0;
}
