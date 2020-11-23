#pragma once
#include <string>
#include <vector>
#include <map>
#include <istream>

using bus_t = std::string;
using stop_t = std::string;
using stops_t = std::vector<stop_t>;

enum class QueryType 
{
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};


struct Query 
{
	QueryType type;
	bus_t bus;
	stop_t stop;
	stops_t stops;
	
	std::map<std::string,QueryType> mQueries
	{
		{"ALL_BUSES", QueryType::AllBuses},
		{"NEW_BUS", QueryType::NewBus},
		{"BUSES_FOR_STOP", QueryType::BusesForStop},
		{"STOPS_FOR_BUS", QueryType::StopsForBus},
	};

	void Input(std::istream&);
	void NewBusCommand(std::istream&);
	void BusesForStopCommand(std::istream&);
	void StopsForBusCommand(std::istream&);
};

std::istream& operator >> (std::istream& is, Query& q);

