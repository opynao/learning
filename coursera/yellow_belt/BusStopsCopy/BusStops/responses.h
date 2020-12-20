#pragma once
#include <string>
#include <vector>
#include <map>
#include <ostream>

using bus_t = std::string;
using stop_t = std::string;

using routes_t = std::vector<bus_t>;
using stops_t = std::vector<stop_t>;

using busInfo_t = std::map<bus_t,stops_t>;
using stopRoutes_t = std::map<stop_t,routes_t>;

struct BusesForStopResponse 
{
	routes_t buses;
};

struct StopsForBusResponse 
{
	std::pair<stopRoutes_t,stops_t> stops;
};

struct AllBusesResponse 
{
	busInfo_t BusStops;

};

void PrintSpace(std::ostream& os, size_t& vSize, size_t& counter);
void PrintStopsForBus(std::ostream& os, const StopsForBusResponse& r);
void PrintAllBuses(std::ostream& os, const AllBusesResponse& r);
void PrintBusesForStop(std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
