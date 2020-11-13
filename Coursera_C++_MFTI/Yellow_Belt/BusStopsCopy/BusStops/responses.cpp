#include <iostream>
#include <algorithm>
#include <functional>
#include "responses.h"

void PrintSpace(std::ostream& os, size_t& vSize, size_t& counter)
{
	if(counter != vSize-1)
	{	
		os << " ";
		counter ++;
	}
}

void PrintStopsForBus(std::ostream& os, const StopsForBusResponse& r)
{
	stopRoutes_t stopRoutes = r.stops.first;
	stops_t stops = r.stops.second;
	for(const auto& stop : stops)
	{
		os << "Stop " << stop << ": ";
	
		if(stopRoutes.at(stop).empty())
			os << "no interchange" << std::endl;
	
		else
		{
			size_t vSize =stopRoutes.at(stop).size();
			size_t counter {0};
	
			for(const auto& bus : stopRoutes.at(stop))
			{
				os << bus;
				PrintSpace(os, vSize, counter);	
			}
			os << std::endl;
		}
	}
}

void PrintAllBuses(std::ostream& os, const AllBusesResponse& r)
{
	for(const auto& busRoute : r.BusStops)
		{
			os << "Bus " << busRoute.first << ": ";
			size_t vSize = busRoute.second.size();
			size_t counter {0};
			for(const auto& stop : busRoute.second)
			{
				os << stop;
				PrintSpace(os, vSize, counter);
			}
			os << std::endl;
		}
}


void PrintBusesForStop(std::ostream& os, const BusesForStopResponse& r)
{	
	size_t vSize = r.buses.size();
	size_t counter {0};
	for(const auto& bus : r.buses)
	{
		os << bus;
		PrintSpace(os, vSize, counter);		
	}	
	os << std::endl;
}

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) 
{
	if(r.buses.empty())
		os << "No stop\n";
	else
	{
		PrintBusesForStop(os,r);
	}
	return os;
}



std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) 
{
	stopRoutes_t stopRoutes = r.stops.first;
	if(stopRoutes.empty())
		os << "No bus" << std::endl;
	else
	{
		PrintStopsForBus(os,r);
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) 
{
	if(r.BusStops.empty())
		os << "No buses" << std::endl;
	else
	{
		PrintAllBuses(os,r);
	}
	return os;
}


