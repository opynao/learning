#include <map>
#include <string>
#include <iterator>
//#include "names_surnames.h"

using personDatas_t = std::map<int,std::pair<std::string,std::string>,std::greater<int>>;
using Name_t = std::string;
using Year_t = int;

class Person
{
private:
	Name_t first_name {};
	Name_t last_name {};
	personDatas_t m_personData {};

private:

	Name_t GetFirstName(personDatas_t::const_iterator) const;
	Name_t GetLastName(personDatas_t::const_iterator) const;

public:
	Person() {}
	void ChangeFirstName(const Year_t, const Name_t&);
	void ChangeLastName(const Year_t, const Name_t&);
	Name_t GetFullName(const Year_t) const;
};
void Person::ChangeFirstName(const Year_t year, const Name_t& first_name)
{
	m_personData[year].first = first_name;
}
    
void Person::ChangeLastName(const Year_t year, const Name_t& last_name)
{
	m_personData[year].second = last_name;
}

Name_t Person::GetFullName(const Year_t year) const
{
	const auto itLastChangeYear {m_personData.lower_bound(year)};
	
	if(itLastChangeYear == m_personData.cend())
		return "Incognito";
	
	const std::string firstName = GetFirstName(itLastChangeYear);
	const std::string lastName = GetLastName(itLastChangeYear);		

	if(firstName.empty())
		return {lastName + " with unknown first name"};

	if(lastName.empty())
		return {firstName + " with unknown last name"};

	return {firstName + " " + lastName};
}

std::string Person::GetFirstName(personDatas_t::const_iterator itBegin) const
{
	while(itBegin != m_personData.cend())
	{
		if(!itBegin->second.first.empty())
			return itBegin->second.first;
		++itBegin;
	}
	return "";
}

std::string Person::GetLastName(personDatas_t::const_iterator itBegin) const
{
	while(itBegin != m_personData.cend())
	{
		if(!itBegin->second.second.empty())
			return itBegin->second.second;
		++itBegin;
	}
	return "";
}
