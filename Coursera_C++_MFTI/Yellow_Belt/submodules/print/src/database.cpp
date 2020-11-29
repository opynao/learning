#include "database.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

void Database::Add( const Date& date, const std::string& event )
{
	if(std::count(db[date].begin(),db[date].end(),event))
			return;
	db[date].push_back(event);
}

void Database::Print(std::ostream& os) const
{
	for(const auto& dateEvents : db)
	{
		const Date& date = dateEvents.first;
		std::for_each(dateEvents.second.cbegin(),dateEvents.second.cend(),[&date, &os](const std::string& event)
				{
					os << std::setw(4) << std::setfill('0') << date.GetYear() << '-' << std::setw(2) << date.GetMonth() << '-' << std::setw(2) << date.GetDay() << ' ' << event << std::endl;
				});
	}
}
/*
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

*/
