#include <string>
#include <map>
#include <iostream>
#include <functional>
#include <cctype>
#include <sstream>
#include <cassert>
#include <set>
#include <iomanip>
#include <algorithm>
#define LOGF //std::cerr << __FUNCTION__ << std::endl


class Date 
{
public:
	Date() = default;
	explicit Date(const std::string&);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	static bool CheckFormat(const std::string&);
private:
	int year {};
	int month {};
	int day {};
};

bool operator<(const Date& lhs, const Date& rhs)
{

	if(lhs.GetYear() < rhs.GetYear())
		return true;
	
	if(lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth())
		return true;
	
	if(lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() < rhs.GetDay())
		return true;
	return false;
}

Date::Date(const std::string& strDate)
{
	std::istringstream is (strDate);
	is >> year;
	is.get();
	is >> month;
	is.get();
	is >> day;
}

int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

bool Date::CheckFormat(const std::string& date)
{
	if(date.empty())
		return false;
	size_t i = 0;

	for( size_t j : {1,2,3} )
	{
		if(date[i] == '-' || date[i] == '+')
	        	++i;
		
		if (!std::isdigit(date[i]))
			return false;
	
		while(std::isdigit(date[i]) && i < date.size() - 1)
			++i;

		if( j == 3 && !std::isdigit(date[i]))
			return false;
		
		if (j != 3)
		{
			if( date[i++] != '-')
				return false;
		}
	}

	if( i == date.size() - 1)
		return true;
	
	return false;
}

/*
void PrintSet(const std::set<std::string>& set)
{
	for(const auto& elem : set)
		std::cerr << elem << ',';
}


void PrintMap(const std::map<Date,std::set<std::string>>& map)
{
	std::cerr << '{';
	for(auto& elem : map)
	{
		std::cerr << '{' << elem.first.GetYear() << '-' << elem.first.GetMonth() << '-'<< elem.first.GetDay() << ',' ;
		PrintSet(elem.second);
		std::cerr << '}';
	}
	std::cerr << '}' << std::endl;
}
*/

class Database {
public:
	void AddEvent(const Date& date, const std::string& event);
	bool DeleteEvent(const Date& date, const std::string& event);
	int  DeleteDate(const Date& date);
	std::set<std::string> Find(const Date& date) const;
	void Print(std::ostream&) const;
private:
	std::map<Date, std::set<std::string>> db;
};

void Database::AddEvent( const Date& date, const std::string& event )
{
	db[date].insert(event);
}


bool Database::DeleteEvent(const Date& date, const std::string& event)
{
	auto it = db.find(date);
	if(db.cend() != it && it->second.erase(event))
		return true;
	return false;
}

int Database::DeleteDate(const Date& date)
{
	auto it = db.find(date);
	if(it == db.cend())
		return 0;
	int numberOfEvents = it->second.size();
	db.erase(date);
	return numberOfEvents;
}

std::set<std::string> Database::Find(const Date& date) const
{
	return db.find(date)->second;
}

void Database::Print(std::ostream& os) const
{
	for(const auto& dateEvents : db)
	{
		const Date& date = dateEvents.first;
		if(date.GetYear() < 0)
			continue;
		
		std::for_each(dateEvents.second.cbegin(),dateEvents.second.cend(),[&date, &os](const std::string& event)
				{
					os << std::setw(4) << std::setfill('0') << date.GetYear() << '-' << std::setw(2) << date.GetMonth() << '-' << std::setw(2) << date.GetDay() << ' ' << event << std::endl;
				});
	}
}


class Parser
{
public:
	bool Parse(const std::string&);
private:
	bool ParseAddCommand(const std::string&);
	bool ParseDelCommand(const std::string&);
	bool ParseFindCommand(const std::string&);
	bool ParsePrintCommand(const std::string&);
	void OnParseError();
	bool ParseDate(const std::string& strDateFormat,Date& date);
private:
	std::map<std::string,bool(Parser::*)(const std::string&)> mParsers 
	{ {"Add", &Parser::ParseAddCommand},
	  {"Del", &Parser::ParseDelCommand},
   	  {"Find", &Parser::ParseFindCommand},
	  {"Print", &Parser::ParsePrintCommand}	  
	};

	Database db;
};

bool Parser::Parse(const std::string& str)
{
	if(str.empty())
		return true;
	std::istringstream is (str);
	std::string cmd;
	is >> cmd;
	auto it = mParsers.find(cmd);
	if(mParsers.cend() != it)
	{
		return std::bind(it->second,this,str.substr(cmd.size(),str.size()-cmd.size()))();
	}
	std::cout << "Unknown command: " << cmd << std::endl;
	return false;
}


bool Parser::ParseAddCommand(const std::string& str)
{
	std::istringstream ss (str);
	std::string strDate, event;
	Date date;
	ss >> strDate;
	if(!ParseDate(strDate,date))
		return false;
	ss >> event;
	db.AddEvent(date, event);
	return true;
}


bool Parser::ParseDate(const std::string& strDateFormat, Date& date)
{
	if(!Date::CheckFormat(strDateFormat))
	{
		std::cout << "Wrong date format: " << strDateFormat << std::endl;
		return false;
	}

	date = Date(strDateFormat);
	
	if(date.GetMonth() < 1 || date.GetMonth() > 12)
	{
		std::cout << "Month value is invalid: " << date.GetMonth() << std::endl;
		return false;
	}
		
	if(date.GetDay() < 1 || date.GetDay() > 31)
	{
		std::cout << "Day value is invalid: " << date.GetDay() << std::endl;
		return false;
	}

	return true;
}


bool Parser::ParseDelCommand(const std::string& str)
{
	std::istringstream ss (str);
	std::string strDate, event;
	Date date;
	ss >> strDate;

	if(!ParseDate(strDate,date))
		return false;
	
	if(ss.eof())
	{
		std::cout << "Deleted " << db.DeleteDate(date) << " events" << std::endl;
		return true;
	}
	
	ss >> event;
	
	if(!db.DeleteEvent(date, event))
		std::cout << "Event not found" << std::endl;
	else
		std::cout << "Deleted successfully" << std::endl;
	return true;
}

bool Parser::ParseFindCommand(const std::string& str)
{
	std::istringstream ss (str);
	std::string strDate, event;
	Date date;
	ss >> strDate;

	if(!ParseDate(strDate,date))
		return false;
	
	const std::set<std::string>& sEvents = db.Find(date);

	for( const auto& event : sEvents)
		std::cout << event << std::endl;
	return true;
}

bool Parser::ParsePrintCommand(const std::string&)
{
	db.Print(std::cout);
	return true;
}


void testCheckFormat_CorrectDate()
{
	LOGF;
	assert(true == Date::CheckFormat("1-1-1"));
	assert(true == Date::CheckFormat("-1-1-1"));
	assert(true == Date::CheckFormat("1--1-1"));
	assert(false == Date::CheckFormat("1---1-1"));
	assert(true == Date::CheckFormat("1-+1-+1"));
	assert(true == Date::CheckFormat("-1-1-1"));
	assert(false == Date::CheckFormat("--1-1-1"));
	assert(false == Date::CheckFormat("-1-1"));
	assert(false == Date::CheckFormat("1-1-"));
	assert(false == Date::CheckFormat("&1-1-1"));
	assert(false == Date::CheckFormat("1-1-1-"));
}

void testPrint()
{
	Parser pr;
	pr.Parse("Add 0-1-2 event1");
	pr.Parse("Add 1-2-3 event2");
	pr.Parse("Add -1-2-3 event3");
	pr.Parse("Add 0-1-2 event4");
	pr.Parse("Add 0-1-2 event5");
	pr.Parse("Print");
}

void testOperatorLessForDate()
{
	Date dateFirst("0-1-2");
	Date dateSecond("0-1-2");
	assert(false == (dateFirst < dateSecond));
}


int main()
{
	std::string str;
	Parser pr;
	while(std::getline(std::cin,str))
	{
		if(!pr.Parse(str))
			return 0;
	}
	return 0;
}
