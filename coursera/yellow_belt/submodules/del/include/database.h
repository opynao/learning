#pragma once

#include "date.h"

#include <vector>
#include <string>
#include <map>
#include <ostream>

using Event_t = std::string;
//using Pred_t = bool(*) (const Date&, const Event_t&);

class Database {
public:
	void Add(const Date&, const Event_t&);
	void Print(std::ostream&) const;
	template<typename T> int RemoveIf(T pred);
//	std::set<std::string> FindIf(auto predicate) const;
	std::string Last(const Date&) const;
private:
	std::map<Date, std::vector<Event_t>> db_;
};

template <typename T>
int Database::RemoveIf(T pred)
{
	int entries {};
	bool i = pred(db_.begin()->first,db_.begin()->second.back());
/*	for(auto& date : db_ )
	{
		for (auto& event : date )
		{
			auto itDel = (std::remove_if( db_.begin(), db_.end(), pred(date, event) ));
			for(auto it = itDel ; it != db_.end(); ++it)
			{
				entries += it->second.size();
			}
		}
	}
	db_.erase(itDel, db_.end());
*/	if(i == 0)
		return entries+1;
	return entries;
}

