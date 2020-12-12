#pragma once

#include "date.h"

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include <functional>
#include <set>

template <typename T>
void DeleteEmptyEvents(T& m)
{
	for(auto iter = m.begin(); iter != m.end(); ) 
	{
		if (iter->second.empty())
          iter = m.erase(iter);
		else 
          ++iter;
	}
}

using Event_t = std::string;
using Database_t = std::map<Date, std::vector<Event_t>>;
using DatabaseSet_t = std::map<Date, std::set<Event_t>>;
using vEvents_t = std::vector<std::pair<Date, Event_t>>;

class Database 
{
public:
	void Add(const Date&, const Event_t&);
	void Print(std::ostream&) const;
	int RemoveIf(std::function <bool ( Date, Event_t )>);
	vEvents_t FindIf(std::function<bool ( Date, Event_t )>) const;
	std::pair< Date, Event_t > Last(const Date&) const;
	size_t GetDatabaseSize() const;
	size_t GetEventsCountByDate(const Date&) const;
private:
	Database_t db_;
	DatabaseSet_t db_set;
};

std::ostream& operator <<(std::ostream& os, const std::pair<const Date, const std::vector<Event_t>>& pr);
std::ostream& operator <<(std::ostream& os, const std::pair<const Date,const Event_t>& pr);
