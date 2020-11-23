#pragma once

#include "date.h"
#include "event.h"
#include "condition.h"

#include <set>
#include <string>
#include <map>
#include <ostream>


class Database {
public:
	void Add(const Date&, const Event&);
	void Print(std::ostream&) const;
	int RemoveIf(auto predicate);
	std::set<std::string> FindIf(auto predicate) const;
	Condition Last(const Date&);
private:
	std::map<Date, std::set<std::string>> db;
};
