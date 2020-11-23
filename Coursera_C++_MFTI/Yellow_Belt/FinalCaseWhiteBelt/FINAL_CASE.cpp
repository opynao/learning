#include <string>
#include <map>
#include <set>
#include <iterator>
#include <iostream>


class Database;
class Date;


using date_t = std::string;
using event_t = std::string;
using sEvents_t = std::set<event_t>;
using database_t = std::map<Date,sEvents_t>;
using commandName_t = std::string;
using mInput_t = std::map<commandName_t,void(*)(Database&)>;


void AddEventCommand(Database&);
void DeleteCommand(Database&);
void FindEventsOnDateCommand(Database&);
void PrintAllEventsCommand(Database&);


mInput_t mInputCases
{
	{"Add",&AddEventCommand},
	{"Del",&DeleteCommand},
	{"Find",&FindEventsOnDateCommand},
	{"Print",&PrintAllEventsCommand}
};

//----------------CLASS-DATE-----------------

class Date 
{
public:
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	void TransformToString();
	date_t GetDate() const;
	void Input(std::istream&);
private:
	int year;
	int month;
	int day;
	date_t date;
};


bool operator < (const Date& lhs, const Date& rhs)
{
	return true;
}

void Date::Input(std::istream& is)
{

}

std::istream& operator >> (std::istream& is, Date& date)
{
	date.Input(is);
	return is;
}

//----------------CLASS-DATABASE---------------


class Database 
{
public:
	void AddEvent(const Date&, const event_t&);
	bool DeleteEvent(const Date&, const event_t&);
	int  DeleteDate(const Date&);
	sEvents_t Find(const Date&) const;
	void Print() const;
private:
	database_t m_database {};
};


void Database::AddEvent(const Date& date, const event_t& event)
{
        m_database[date].insert(event);
}


bool Database::DeleteEvent(const Date& date, const event_t& event)
{
	auto it = m_database.find(date);
	if(m_database.end() != it)
	{
		it->second.erase(event);
		return true;
	}
	return false;
}


int Database::DeleteDate(const Date& date)
{
	auto it = m_database.find(date);
	int numberOfEvents {};
	if( m_database.cend() != it )
	{
		numberOfEvents = it->second.size();
		it->second.clear();
	}
	return numberOfEvents;
}	

sEvents_t Database::Find(const Date& date) const
{
	auto it = m_database.find(date);
	return it->second;
}

void Database::Print() const 
{

}



//---------------COMMAND-HANDLER------------------

void CommandHandler(Database& db)
{
	commandName_t command;
	std::cin >> command;
	auto itCall = mInputCases.find(command);
	if(mInputCases.cend() != itCall)
	{
		itCall->second(db);
	}
}

void AddEventCommand(Database& db)
{
	Date date;
	std::cin >> date;
	event_t event;
	std::cin >> event;
	db.AddEvent(date,event);
}

void DeleteCommand(Database& db)
{
	Date date;
	event_t event;
	std::cin >> date;
	std::string str;
	std::getline(std::cin,str);
	if(str != "Add" && str != "Find" && str != "Print")
	{
		str = event;
		bool result = db.DeleteEvent(date,event);
		if(result)
			std::cout << "Deleted successfully" << std::endl;
		else
			std::cout << "Event not found" << std::endl;
	}
	else
	{
		//unget str to stream
		int numberOfEvents = db.DeleteDate(date);
		std::cout << "Deleted " << numberOfEvents << " events";
	}
}

void FindEventsOnDateCommand(Database& db)
{
	Date date;
	std::cin >> date;
	sEvents_t sEvents;
	sEvents = db.Find(date);
	for(const auto& event : sEvents)
		std::cout << event << std::endl;
}

void PrintAllEventsCommand(Database& db)
{
	db.Print();
}

//-------------------------------MAIN------------------


int main() 
{
	Database db;
	while (std::cin)
       	{
		CommandHandler(db);// Считайте команды с потока ввода и обработайте каждую
	}
	return 0;
}
