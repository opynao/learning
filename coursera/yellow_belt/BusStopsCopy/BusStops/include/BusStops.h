#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <ostream>
#include <istream>

using bus_t = std::string;
using stop_t = std::string;

using routes_t = std::vector<bus_t>;
using stops_t = std::vector<stop_t>;

using busInfo_t = std::map<bus_t,stops_t>;
using stopRoutes_t = std::map<stop_t,routes_t>;

enum class QueryType 
{
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

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

class BusManager 
{
private:
	busInfo_t m_busRoutes {};
	routes_t m_vBuses {};
public:
	void AddBus(const bus_t&, const stops_t&); 
	BusesForStopResponse GetBusesForStop(const std::string&) const;
	StopsForBusResponse GetStopsForBus(const std::string&) const;
	AllBusesResponse GetAllBuses() const;
	routes_t GetBusRoutesForStop(const stop_t&) const;
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

void PrintSpace(std::ostream& os, size_t& vSize, size_t& counter);
void PrintStopsForBus(std::ostream& os, const StopsForBusResponse& r);
void PrintAllBuses(std::ostream& os, const AllBusesResponse& r);
void PrintBusesForStop(std::ostream& os, const BusesForStopResponse& r);
std::istream& operator >> (std::istream& is, Query& q);
std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);


class RoutesCollector
{
public:
	explicit RoutesCollector (const stop_t& stop);
	void operator () (busInfo_t::const_reference busRoute);
	routes_t GetRoutes() const;
private:
	bool StopOnRoute(const busInfo_t::mapped_type& stops) const;
	const stop_t& m_Stop;
	routes_t m_BusRoutesForStop;
};



