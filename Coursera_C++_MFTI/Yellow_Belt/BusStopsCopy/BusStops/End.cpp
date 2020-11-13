#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <ostream>
#include <istream>
#include <iostream>
#include <algorithm>
#include <functional>
#define LOGF std::cerr << __FUNCTION__ << std::endl


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

std::istream& operator >> (std::istream& is, Query& q) 
{
	q.Input(is);
	return is;
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


//------------------END-OF-OVERLOADED-OPERATORS--------------------


//-------------------STRUCT-QUERY--------------------------


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

//-------------------END-OF-STRUCT-QUERY-------------------------------

//-----------------------CLASS-BUS-MANAGER-----------------------------

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

int main()
{
	return 0;
}
