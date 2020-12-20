#pragma once
#include <map>
#include <string>
#include <iterator>

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
