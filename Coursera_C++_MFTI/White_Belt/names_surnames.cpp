#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <utility>
#include <cassert>
#include <memory>
#include <vector>
#include <sstream>

#define LOG ;
//std::cerr << __FUNCTION__ << std::endl;

using firstName_t = std::string;
using lastName_t = std::string;
using year_t = size_t;
using personDatas_t = std::map<year_t,std::pair<firstName_t,lastName_t>,std::greater<year_t>>;

class Person
{
public:
	Person(const firstName_t& firstName, const lastName_t& lastName, const year_t birthYear)
		: m_birthYear {birthYear}
 	{
		m_personData.emplace(birthYear,std::make_pair(firstName, lastName));
	}

	void ChangeFirstName(const year_t year, const firstName_t& first_name)
	{
		LOG;
		if(year < m_birthYear)
			return;
		m_personData[year].first = first_name;
	}

	void ChangeLastName(const year_t year, const lastName_t& last_name)
	{
		LOG;
		if(year < m_birthYear)
			return;
		m_personData[year].second = last_name;
	}

	std::string GetFullName(const year_t year) const
	{
		LOG;
		std::string result {};
		if(year < m_birthYear)
			return "No person";
		const auto itLastChangeYear {m_personData.lower_bound(year)};
	    //    if(itLastChangeYear == m_personData.cend())
	//		return "Incognito";
		
		const firstName_t firstName = GetFirstName(itLastChangeYear);
		const lastName_t lastName = GetLastName(itLastChangeYear);		

		if(firstName.empty())
			return {lastName + " with unknown first name"};

		if(lastName.empty())
			return {firstName + " with unknown last name"};

		return {firstName + " " + lastName};
	}

	std::vector<firstName_t> GetFirstNameWithHistory(const year_t year) const
	{
		std::vector<firstName_t> vFirstNames {};
		auto itBegin {m_personData.lower_bound(year)};
		while(itBegin != m_personData.cend())
		{
			if(!itBegin->second.first.empty())
				vFirstNames.push_back(itBegin->second.first);
			++itBegin;
		}
		const auto itLast = std::unique(std::begin(vFirstNames),std::end(vFirstNames));
		vFirstNames.erase(itLast,vFirstNames.end());
	        return vFirstNames;
	}

	std::vector<lastName_t> GetLastNameWithHistory(const year_t year) const
	{
		std::vector<lastName_t> vLastNames {};
		auto itBegin {m_personData.lower_bound(year)};
		while(itBegin != m_personData.cend())
		{
			if(!itBegin->second.second.empty())
				vLastNames.push_back(itBegin->second.second);
			++itBegin;
		}
		const auto itLast = std::unique(std::begin(vLastNames),std::end(vLastNames));
		vLastNames.erase(itLast,vLastNames.end());
	        return vLastNames;
	}

	static void AppendHistory(const std::vector<std::string> vNames, std::string& out_result)
	{
		if(vNames.size() > 1)
		{
			out_result += " (";
			for(size_t i = 1; i <vNames.size(); ++i)
			{
				out_result += (vNames[i] + ", ");
			}
			out_result.erase(out_result.size()-2,2);
			out_result += ")";
		}
	}	

	std::string GetFullNameWithHistory(const year_t year) const
	{
		const auto vFirstNames {GetFirstNameWithHistory(year)};
		const auto vLastNames {GetLastNameWithHistory(year)};
		std::string result {};
		if(year < m_birthYear)
			return "No person";
	//	if(vFirstNames.empty() && vLastNames.empty())
	//		return "Incognito";
		if(vFirstNames.empty())
		{
			result = vLastNames.front();
			AppendHistory(vLastNames,result);
			result += " with unknown first name";
			return result;
		}
		if(vLastNames.empty())
		{
			result = vFirstNames.front();
			AppendHistory(vFirstNames,result);
			result += " with unknown last name";
			return result;
		}
		result = vFirstNames.front();
		AppendHistory(vFirstNames,result);
		result += (" " + vLastNames.front());
		AppendHistory(vLastNames,result);
		return result;
	}

private:

	firstName_t GetFirstName(personDatas_t::const_iterator itBegin) const
	{
		while(itBegin != m_personData.cend())
		{
			if(!itBegin->second.first.empty())
				return itBegin->second.first;
			++itBegin;
		}
		return "";
	}

	lastName_t GetLastName(personDatas_t::const_iterator itBegin) const
	{
		LOG;
		while(itBegin != m_personData.cend())
		{
			if(!itBegin->second.second.empty())
				return itBegin->second.second;
			++itBegin;
		}
		return "";
	}

private:

	const year_t m_birthYear;	
	firstName_t first_name {};
	lastName_t last_name {};
	personDatas_t m_personData {};
};

//------------------------------------------------------------------------------------

void testPerson_ChangeLastAndFirstName_GetFullNameReturnsLastAndFirstName()
{
	LOG;
	const auto upPerson = std::make_unique<Person>("Viktoria","Gorbachyova",1996);
	upPerson->ChangeLastName(1996,"Gorbachyova");
	upPerson->ChangeFirstName(1996,"Viktoria");
	std::string result = "Viktoria Gorbachyova";
	assert(result == upPerson->GetFullName(1996));
}

/*
void testPerson_ChangeLastName_GetFullNameReturnsLastNameWithUnknownFirstName()
{
	LOG;
	const auto upPerson = std::make_unique<Person>("Viktoria","Gorbachyova",1996);
	upPerson->ChangeLastName(1996,"Gorbachyova");
	std::string result = "Gorbachyova with unknown first name";
	assert(result == upPerson->GetFullName(1996));
}


void testPerson_ChangeFirstName_GetFullNameReturnsFirstNameWithUnknownLastName()
{
	const auto upPerson = std::make_unique<Person>("Viktoria","Gorbachyova",1996);
	upPerson->ChangeFirstName(1996,"Viktoria");
	std::string result = "Viktoria with unknown last name";
	assert(result == upPerson->GetFullName(1996));
}
*/

void testPerson_GetFirstNameWithHistory()
{
	const auto upPerson = std::make_unique<Person>("Viktoria","Gorbachyova",1996);
	upPerson->ChangeFirstName(1996,"Viktoria");
	upPerson->ChangeFirstName(2000,"Vika");
	upPerson->ChangeFirstName(2021,"Vik");
	const std::vector<firstName_t> result {"Vik","Vika","Viktoria"};
	assert(result == upPerson->GetFirstNameWithHistory(2021));
}


void testPerson_GetFirstNameWithHistory_IgnoreConsecutiveMatches()
{
	const auto upPerson = std::make_unique<Person>("Viktoria","Gorbachyova",1996);
	upPerson->ChangeFirstName(1996,"Vika");
	upPerson->ChangeFirstName(2000,"Vika");
	upPerson->ChangeFirstName(2021,"Vik");
	upPerson->ChangeFirstName(2025,"Vika");
	upPerson->ChangeFirstName(2026,"Vik");
	const std::vector<firstName_t> result {"Vik","Vika","Vik","Vika"};
	assert(result == upPerson->GetFirstNameWithHistory(2026));
}

/*
void testPerson_GetFullNameWithHistory()
{
	std::stringstream cout; 
	Person person("Polina","Sergeeva",1960);
  	person.ChangeFirstName(1965, "Polina");
  	person.ChangeLastName(1967, "Sergeeva");
 	
       	for (int year : {1900, 1965, 1990})
       	{
   		cout << person.GetFullNameWithHistory(year) << std::endl;
	}
	std::cerr << cout.str() << std::endl;
	assert(cout.str() == "Incognito\nPolina with unknown last name\nPolina Sergeeva\n");
 	cout.str("");

	person.ChangeFirstName(1970, "Appolinaria");
 	for (int year : {1969, 1970})
       	{
		cout << person.GetFullNameWithHistory(year) << std::endl;
	}
  	std::cerr << cout.str() << std::endl;
	assert(cout.str() == "Polina Sergeeva\nAppolinaria (Polina) Sergeeva\n");
	cout.str("");

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970})
       	{
  		cout << person.GetFullNameWithHistory(year) << std::endl;
	}
  	std::cerr << cout.str() << std::endl;
	assert(cout.str() == "Polina Volkova (Sergeeva)\nAppolinaria (Polina) Volkova (Sergeeva)\n");
	cout.str("");

	person.ChangeFirstName(1990, "Polina");
  	person.ChangeLastName(1990, "Volkova-Sergeeva");
 	cout << person.GetFullNameWithHistory(1990) <<std::endl;
  	std::cerr << cout.str() << std::endl;
	assert(cout.str() == "Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)\n");
	cout.str("");
	
	person.ChangeFirstName(1966, "Pauline");
	cout << person.GetFullNameWithHistory(1966) <<std::endl;	std::cerr << cout.str() << std::endl;
	assert(cout.str() == "Pauline (Polina) with unknown last name\n");
	cout.str("");

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967})
       	{
	    cout << person.GetFullNameWithHistory(year) <<std::endl;
 	}	std::cerr << cout.str() << std::endl;
	assert(cout.str() == "Sergeeva with unknown first name\nPauline (Polina) Sergeeva\n");
	cout.str("");
	
	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) <<std::endl;	std::cerr << cout.str() << std::endl;
 	assert(cout.str() == "Pauline (Polina) Sergeeva (Ivanova, Sergeeva)\n");
}
*/

void testPerson_ConstructWithArgs()
{
	const auto upPerson = std::make_unique<Person>("Viktoria","Gorbachyova",1996);
	assert(nullptr != upPerson);	
}

void testPerson_ChangeLastName_ChangeBeforeBirth_ResultNothing()
{
	const auto upPerson = std::make_unique<Person>("Viktoria","Gorbachyova",1996);
	upPerson->ChangeLastName(1992,"Lebedeva");
	std::string result = "Viktoria Gorbachyova";
	assert(result == upPerson->GetFullName(1996));
}

void testPerson_GetFullName_ResultNoPerson()
{
	const auto upPerson = std::make_unique<Person>("Viktoria","Gorbachyova",1996);
	std::string result = "No person";
	assert(result == upPerson->GetFullName(1992));
}


int main()
{
	testPerson_GetFirstNameWithHistory();
	testPerson_ChangeLastAndFirstName_GetFullNameReturnsLastAndFirstName();
	//testPerson_ChangeLastName_GetFullNameReturnsLastNameWithUnknownFirstName();
	//testPerson_ChangeFirstName_GetFullNameReturnsFirstNameWithUnknownLastName();
	testPerson_GetFirstNameWithHistory_IgnoreConsecutiveMatches();
	//testPerson_GetFullNameWithHistory();
	testPerson_ConstructWithArgs();
	testPerson_ChangeLastName_ChangeBeforeBirth_ResultNothing();
	testPerson_GetFullName_ResultNoPerson();
	return 0;
}

