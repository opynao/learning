#pragma once

#include "date.h"

#include <vector>
#include <string>
#include <map>
#include <ostream>

using Event_t = std::string;

class Database {
public:
	void Add(const Date&, const Event_t&);
	void Print(std::ostream&) const;
//	int RemoveIf(auto predicate);
//	std::set<std::string> FindIf(auto predicate) const;
	std::string Last(const Date&) const;
private:
	std::map<Date, std::vector<Event_t>> db_;
};
