#include "database.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream> 
#include <tuple> 

void Database::Add( const Date& date, const Event_t& event )
{
	const auto [ it , inserted ] = db_set[date].insert(event);
	if( inserted )
		db_[date].push_back(event);
}

size_t Database::GetDatabaseSize() const
{
	return db_.size();
}

size_t Database::GetEventsCountByDate(const Date& date) const
{
	const auto itEventsByDate = db_.find(date);
	if( itEventsByDate != db_.cend())
		return itEventsByDate->second.size();
	return 0;
}

void Database::Print(std::ostream& os) const
{
	for(const auto& dateEvents : db_)
		os << dateEvents;
}


std::pair< Date, Event_t > Database::Last(const Date& date) const
{
	if(db_.empty() || date < db_.begin()->first)
		throw std::invalid_argument("");

	const auto itCurrent = db_.lower_bound(date);
	
	if( itCurrent->first == date )
		return { date, itCurrent->second.back() };
	
	if(itCurrent == db_.cend())
	{
		const auto itReturn = std::prev(db_.end());
		return { itReturn->first, itReturn->second.back() };
	}

	const auto itReturn = std::prev(itCurrent);
	return { itReturn->first, itReturn->second.back() };
}


int Database::RemoveIf(std::function <bool ( Date, Event_t )> pred)
{
	int entries {};
	for( auto& prDateEvents : db_)
	{
		const auto& date = prDateEvents.first;
		auto& vEvents = prDateEvents.second;
		auto itDel = std::stable_partition( vEvents.begin(), vEvents.end(), [&date, &pred](const Event_t & event) ->bool { return !pred( date, event );} );
		if( itDel != vEvents.end() )
		{
			entries += std::distance( itDel, vEvents.end() );
			std::move( itDel, vEvents.end(), std::inserter( toDelete[date], toDelete[date].end() ) );
			vEvents.erase( itDel, vEvents.end() );
		}
	}

	for( const auto& [ date, vEvents ] : toDelete )
	{
		for( const auto& event : vEvents )
			db_set[date].erase(event);
	}
	DeleteEmptyEvents(db_);
	DeleteEmptyEvents(db_set);
	return entries;
}


vEvents_t Database::FindIf(std::function <bool ( Date, Event_t )> pred) const
{
	vEvents_t vEvents;
	for(const auto& prDateEvents : db_ )
	{
		auto events = prDateEvents.second;
		const auto& date = prDateEvents.first;
		auto itCopy = std::stable_partition( events.begin(), events.end(), [&date, &pred](const Event_t & event) ->bool { return !pred( date, event );} );
		if( itCopy != events.cend() )
		{
			for( auto iter = itCopy; iter != events.cend(); ++iter)
				vEvents.push_back(std::make_pair(date, *iter));
		}
	}
	return vEvents;
}


std::ostream& operator <<(std::ostream& os, const std::pair<const Date, const std::vector<Event_t>>& pr)
{
	for(const auto& event : pr.second )
		os << pr.first << " " << event << std::endl;
	return os;
}


std::ostream& operator <<(std::ostream& os, const std::pair<const Date,const Event_t>& pr)
{
	os << pr.first << " " << pr.second;
	return os;
}


