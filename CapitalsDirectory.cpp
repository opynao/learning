#include <memory>
#include <cassert>

using countryName_t = std::string;
using capitalName_t = std::string;
using commandName_t = std::string;

enum class Answers
{
	IntroduceNewCountry,
	CountryHasNotChangeCapital,
	CountryHasChangedCapital,
	IncorrectRename,
	CountryHasRenamed,
	CountryDoesNotExist,
	CountryHasCapital,
	ThereAreNoCountries,
	Success
};

std::map<commandName_t,void> mInputCases
{
	{"CHANGE_CAPITAL",&ChangeCapitalCommand()}
	{"ABOUT",&AboutCommand()},
	{"DUMP",&DumpCommand()},
	{"RENAME",&RenameCommand()}
}

std::map<countryName_t,capitalName_t> mCountriesCapitals m {};

void ChangeCapitalCommand(CountryName_t country,CapitalName_t capital)
{
	std::cin >> country >> capital;
	Answers	functionAnswer = ChangeCapital(country,capital);
	if(functionAnswer == Answers::IntroduceNewCountry)
	{
		std::cout << "Introduce new country " << country << " with capital " << capital << std::endl; 
	}
}

Answers ChangeCapital(const countryName_t& countryName, const capitalName_t& capitalName)
{
	if(m.find(countryName) == m.end())
	{
		m_CountriesCapitals.emplace(countryName,capitalName);
		return Answers::IntroduceNewCountry;
	}
	else if(m.find(countryName) != m.end() && m[countryName] == capitalName)
	{
		return Answers::CountryHasNotChangeCapital;
	}
	else(m.find(countryName) != m.end() && m[countryName] != capitalName)
	{
		m[countryName] == capitalName;
		return CountryHasChangedCapital;
	}
}

void CommandHandler(commandName_t command)
{
	mInputCases.find(command);
}

void testChangeCapital_Return_IntroduceNewCountry()
{
	ChangeCapital("Russia","Moscow");
}



int main()
{
	size_t NumberOfCalls {};
	std::vector<std::string> vStrings;
	while(NumberOfCalls--)
	{
		commandName_t commandName;
		CommandHandler(commandName);
	}
	return 0;
}
