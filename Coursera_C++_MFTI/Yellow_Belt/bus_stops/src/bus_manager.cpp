#include <iostream>
#include <algorithm>
#include <functional>
#include "bus_manager.h"

RoutesCollector::RoutesCollector (const stop_t& stop)
		: m_Stop (stop)
{
}

void RoutesCollector::operator () (busInfo_t::const_reference busRoute)
{
	if(StopOnRoute(busRoute.second))
		m_BusRoutesForStop.push_back(busRoute.first);
}


routes_t RoutesCollector::GetRoutes() const
{
	return m_BusRoutesForStop;
}

bool RoutesCollector::StopOnRoute(const busInfo_t::mapped_type& stops) const
{
	return std::any_of(std::cbegin(stops),std::cend(stops),[this](const std::string& stop){return stop == m_Stop;});
}

routes_t BusManager::GetBusRoutesForStop(const stop_t& stop) const
{
	routes_t result {};
	RoutesCollector route(stop);
	
	for(const auto& item : m_vBuses)
	{
		auto itFind = m_busRoutes.find(item);
		route(*itFind);
	}

	result = route.GetRoutes();
	
	return result;
}


StopsForBusResponse BusManager::GetStopsForBus(const bus_t& bus) const 
{
	StopsForBusResponse response;	// bus marshrute
	
	if(m_busRoutes.count(bus) == 0)
		return {};
	
	stops_t vBusStops = m_busRoutes.at(bus);
	
	for(const auto& stop : vBusStops)
	{
		response.stops.second.push_back(stop);
		response.stops.first[stop] = GetBusRoutesForStop(stop); 
	}
	for(auto& stops : response.stops.first)
	{
		auto itFind = std::find(stops.second.cbegin(),stops.second.cend(),bus);
		stops.second.erase(itFind);
	}
	return response;
}

//---ADD-BUS

void BusManager::AddBus(const bus_t& bus, const stops_t& stops) 
{
	m_busRoutes[bus] = stops;
	m_vBuses.push_back(bus);
}

//---GET-BUSES-FOR-STOP

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const 
{
	BusesForStopResponse response;
	response.buses = GetBusRoutesForStop(stop);
	return response;
}

//---ALL-BUSES

AllBusesResponse BusManager::GetAllBuses() const 
{
	AllBusesResponse response;
	response.BusStops = m_busRoutes;
	return response;
}
