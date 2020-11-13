#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

/*
using personDatas_t = std::map<int,std::pair<std::string,std::string>,std::greater<int>>;


class Person
{
private:
	std::string first_name {};
	std::string last_name {};
	personDatas_t m_personData {};

private:

	std::string GetFirstName(personDatas_t::const_iterator itBegin) const;
	std::string GetLastName(personDatas_t::const_iterator itBegin) const;

public:
	Person();
	void ChangeFirstName(const int year, const std::string& first_name);
	void ChangeLastName(const int year, const std::string& last_name);
	std::string GetFullName(const int year) const;
};

Person::Person()
{
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


void Person::ChangeFirstName(const int year, const std::string& first_name)
{
	m_personData[year].first = first_name;
}
    
void Person::ChangeLastName(const int year, const std::string& last_name)
{
	m_personData[year].second = last_name;
}

std::string Person::GetFullName(const int year) const
{
	std::string result {};
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
*/

//------------------------------------------------------------------------------------


void testPerson_ChangeLastAndFirstName_GetFullNameReturnsLastAndFirstName()
{
	Person person;	
	person.ChangeLastName(1996,"Gorbachyova");
	person.ChangeFirstName(1996,"Viktoria");
	std::string result = "Viktoria Gorbachyova";
	AssertEqual( person.GetFullName(1996), result );
}


void testPerson_ChangeLastName_GetFullNameReturnsLastNameWithUnknownFirstName()
{
	Person person;
	person.ChangeLastName(1996,"Gorbachyova");
	std::string result = "Gorbachyova with unknown first name";
	AssertEqual( person.GetFullName(1996), result );
}


void testPerson_ChangeFirstName_GetFullNameReturnsFirstNameWithUnknownLastName()
{
	Person person;
	person.ChangeFirstName(1996,"Viktoria");
	std::string result = "Viktoria with unknown last name";
	AssertEqual( person.GetFullName(1996), result );
}

void testPerson_IsIncognito()
{
	Person person;
	person.ChangeFirstName(1996,"Viktoria");
	std::string result = "Incognito";
	AssertEqual( person.GetFullName(1992), result );
}


void TestAll()
{
	TestRunner runner;
	runner.RunTest( testPerson_ChangeLastAndFirstName_GetFullNameReturnsLastAndFirstName, "testPerson_ChangeLastAndFirstName_GetFullNameReturnsLastAndFirstName" ); 
	runner.RunTest( testPerson_ChangeLastName_GetFullNameReturnsLastNameWithUnknownFirstName, "testPerson_ChangeLastName_GetFullNameReturnsLastNameWithUnknownFirstName" );
	runner.RunTest( testPerson_ChangeFirstName_GetFullNameReturnsFirstNameWithUnknownLastName, "testPerson_ChangeFirstName_GetFullNameReturnsFirstNameWithUnknownLastName" );
	runner.RunTest( testPerson_IsIncognito, "testPerson_IsIncognito" );
}


int main() 
{
	TestAll();
	return 0;
}
