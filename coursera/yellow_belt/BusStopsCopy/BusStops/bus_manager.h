#pragma once
#include <string>
#include <vector>
#include <map>
#include "responses.h"


using bus_t = std::string;
using stop_t = std::string;

using routes_t = std::vector<bus_t>;
using stops_t = std::vector<stop_t>;

using busInfo_t = std::map<bus_t,stops_t>;
using stopRoutes_t = std::map<stop_t,routes_t>;

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


