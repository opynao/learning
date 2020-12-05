#include "database.h"
#include "date.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

void Database::Add( const Date& date, const std::string& event )
{
	if(std::count(db_[date].begin(),db_[date].end(),event))
			return;
	db_[date].push_back(event);
}

void Database::Print(std::ostream& os) const
{
	for(const auto& dateEvents : db_)
	{
		const Date& date = dateEvents.first;
		std::for_each(dateEvents.second.cbegin(),dateEvents.second.cend(),[&date, &os](const std::string& event)
				{
					os << date << event << std::endl;
				});
	}
}

std::string Database::Last(const Date& date) const
{
	if(date < db_.begin()->first)
		throw std::invalid_argument("");
	auto itCurrent = std::find_if(db_.begin(), db_.end(),[&date](const auto& pr)->bool {return date < pr.first || date == pr.first;});
	std::string result;
	if( itCurrent->first == date )
	{
		std::cout << date;
		return itCurrent->second.back();
	}
	auto itPrev = std::prev(itCurrent);
	std::cout << itPrev->first;
	return itPrev->second.back();
}

/*
bool Database::DeleteEvent(const Date& date, const std::string& event)
{
	auto it = db.find(date);
	if(db.cend() != it && it->second.erase(event))
		return true;
	return false;
}
*/
/*
std::set<std::string> Database::Find(const Date& date) const
{
	return db.find(date)->second;
}

*/
