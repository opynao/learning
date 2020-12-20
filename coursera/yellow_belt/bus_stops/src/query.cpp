#include "query.h"

std::istream& operator >> (std::istream& is, Query& q) 
{
	q.Input(is);
	return is;
}

void Query::Input(std::istream& is)
{
	std::string query {};	
	is >> query;
	auto itFind = mQueries.find(query);
	type = itFind->second;
	
	switch(type)
	{
		case QueryType::NewBus:
			NewBusCommand(is);
			break;
		case QueryType::AllBuses:
		        break;
		case QueryType::BusesForStop:
		        BusesForStopCommand(is);
			break;
		case QueryType::StopsForBus:
			StopsForBusCommand(is);
			break;
	}
}


void Query::NewBusCommand(std::istream& is)
{
	stops.clear();
	size_t numberOfStops {};
	is >> bus >> numberOfStops;
	stops.reserve(numberOfStops);
	while(numberOfStops--)
	{
		is >> stop;
		stops.push_back(stop);
	}
}

void Query::BusesForStopCommand(std::istream& is)
{
	is >> stop;
}


void Query::StopsForBusCommand(std::istream& is)
{
	is >> bus;
}


