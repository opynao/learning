#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <functional>
#include "Utils.h"
#define LOGF std::cerr << __FUNCTION__ << std::endl

//-----------------USING-ENUM-CLASS--------------

using namespace std;

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

//------------------CLASS-DEFINITIONS------------------

//---BUSES-FOR-STOP-RESPONSE

struct BusesForStopResponse 
{
	routes_t buses;
};

//---STOPS-FOR-BUS-RESPONSE

struct StopsForBusResponse 
{
	std::pair<stopRoutes_t,stops_t> stops;
};

//---ALL-BUSES-RESPONSE

struct AllBusesResponse 
{
	busInfo_t BusStops;

};

//---BUS-MANAGER

class BusManager 
{
private:
	busInfo_t m_busRoutes {};
public:
	void AddBus(const bus_t&, const stops_t&); 
	BusesForStopResponse GetBusesForStop(const std::string&) const;
	StopsForBusResponse GetStopsForBus(const std::string&) const;
	AllBusesResponse GetAllBuses() const;
	routes_t GetBusRoutesForStop(const stop_t&) const;
};


//---QUERY

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

	void Input(istream&);
	void NewBusCommand(std::istream&);
	void BusesForStopCommand(std::istream&);
	void StopsForBusCommand(std::istream&);
};


//----------------------END-OF-CLASS-DEFINITIONS-------------------------

//----------------------OVERLOADED-OPERATORS---------------------------

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


std::ostream& operator << (ostream& os, const BusesForStopResponse& r) 
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

//---GET-STOPS-FOR-BUS

class RoutesCollector
{
public:
	explicit RoutesCollector (const stop_t& stop)
		: m_Stop (stop)
	{
	}
	void operator () (busInfo_t::const_reference busRoute)
	{
		if(StopOnRoute(busRoute.second))
			m_BusRoutesForStop.push_back(busRoute.first);
	}
	routes_t GetRoutes() const
	{
		return m_BusRoutesForStop;
	}

private:
	bool StopOnRoute(const busInfo_t::mapped_type& stops) const
	{
		return std::any_of(std::cbegin(stops),std::cend(stops),[this](const std::string& stop){return stop == m_Stop;});
	}
	const stop_t& m_Stop;
	routes_t m_BusRoutesForStop;
};



routes_t BusManager::GetBusRoutesForStop(const stop_t& stop) const
{
	routes_t result {};
	RoutesCollector route(stop);
	
	
	for(const auto& item : m_busRoutes)
	{
		route(item);
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


//----------------------END-OF-CLASS-BUS-MANAGER-------------------------



//-------------------TESTS----------------------------------

//-------------------TESTS-INPUT-------------------

void testQuery_AllBuses_Operator_Input()
{
	Query query;
	std::string ss {"ALL_BUSES"};
	std::istringstream is (ss);
	is >> query;
	assert(query.type == QueryType::AllBuses);
}

void testQuery_NewBus_Operator_Input()
{
	Query query;
	std::string ss {"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"};
	std::istringstream is (ss);
	is >> query;
	stops_t result {"Tolstopaltsevo","Marushkino", "Vnukovo"};
	assert(query.type == QueryType::NewBus);
	assert(query.bus == "32");
	assert(query.stops.size() == 3);
	assert(query.stops == result);
}


void testQuery_BusesForStop_Operator_Input()
{
	Query query;
	std::string ss {"BUSES_FOR_STOP Vnukovo"};
	std::istringstream is (ss);
	is >> query;
	assert(query.type == QueryType::BusesForStop);
	assert(query.stop == "Vnukovo");
}

void testQuery_StopsForBus_Operator_Input()
{
	Query query;
	std::string ss {"STOPS_FOR_BUS 32K"};
	std::istringstream is (ss);
	is >> query;
	assert(query.type == QueryType::StopsForBus);
	assert(query.bus == "32K");
}



//-------------------END-TESTS-OF-INPUT----------------------



//-------------------TEST-CLASS-BUS-MANAGER--------------------



void testBusManager_AddBus_StopsForBus()
{
	Query query1;
	BusManager bm;
	StopsForBusResponse response;
	std::string ss {"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"};
	std::istringstream is (ss);
	is >> query1;
	bm.AddBus(query1.bus,query1.stops);
	
	Query query2;
	ss = "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo";
	is.clear();
	is.str(ss);
	is >> query2;
	bm.AddBus(query2.bus,query2.stops);

	Query query3;
	ss = "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo";
	is.clear();
	is.str(ss);
	is >> query3;
	bm.AddBus(query3.bus,query3.stops);
	
	Query query4;
	ss = "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo";
	is.clear();
	is.str(ss);
	is >> query4;
	bm.AddBus(query4.bus,query4.stops);

	Query query5;
	ss = "STOPS_FOR_BUS 272";
	is.clear();
	is.str(ss);
	is >> query5;
	response = bm.GetStopsForBus(query5.bus);
	std::ostringstream os;
	os << response;
//	std::cerr << os.str();
	std::string result {"Stop Vnukovo: 32 32K 950\nStop Moskovsky: no interchange\nStop Rumyantsevo: no interchange\nStop Troparyovo: 950\n"};

	assert(os.str() == result);
}

void testRoutesCollector()
{
	RoutesCollector routes("Vnukovo");
	busInfo_t busFirst { {"32", {"Tolstopaltsevo","Marushkino", "Vnukovo"}} };
	routes_t result {"32"};
	routes(*busFirst.begin());
	assert(result == routes.GetRoutes());
	busFirst.emplace( "44",std::vector<std::string> {"a","b","Vnukovo"} );
	result.push_back("44");
	routes(*std::next(busFirst.begin()));
	assert(result == routes.GetRoutes());
}

void testGetBusRoutesForStop()
{
	Query query1;
	BusManager bm;
	std::string ss {"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"};
	std::istringstream is (ss);
	is >> query1;
	bm.AddBus(query1.bus,query1.stops);
	
	Query query2;
	ss = "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo";
	is.clear();
	is.str(ss);
	is >> query2;
	bm.AddBus(query2.bus,query2.stops);

	Query query3;
	ss = "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo";
	is.clear();
	is.str(ss);
	is >> query3;
	bm.AddBus(query3.bus,query3.stops);
	
	routes_t result {"32","32K","950"};
	
	routes_t out = bm.GetBusRoutesForStop("Vnukovo");

	assert(out == result);
}

void testBusManager_AllBuses()
{
	Query query1;
	BusManager bm;
	AllBusesResponse response;
	std::string ss {"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"};
	std::istringstream is (ss);
	is >> query1;
	bm.AddBus(query1.bus,query1.stops);
	
	Query query2;
	ss = "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo";
	is.clear();
	is.str(ss);
	is >> query2;
	bm.AddBus(query2.bus,query2.stops);

	Query query3;
	ss = "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo";
	is.clear();
	is.str(ss);
	is >> query3;
	bm.AddBus(query3.bus,query3.stops);
	
	Query query4;
	ss = "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo";
	is.clear();
	is.str(ss);
	is >> query4;
	bm.AddBus(query4.bus,query4.stops);

	Query query5;
	ss = "ALL_BUSES";
	is.clear();
	is.str(ss);
	is >> query5;
	response = bm.GetAllBuses();
	std::ostringstream os;
	os << response;

	std::string result {"Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo\nBus 32: Tolstopaltsevo Marushkino Vnukovo\nBus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo\nBus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo\n"};

	assert(os.str() == result);
}

void testBusManager_GetBusesForStop()
{
	Query query1;
	BusManager bm;
	BusesForStopResponse response;
	std::string ss {"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"};
	std::istringstream is (ss);
	is >> query1;
	bm.AddBus(query1.bus,query1.stops);
	
	Query query2;
	ss = "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo";
	is.clear();
	is.str(ss);
	is >> query2;
	bm.AddBus(query2.bus,query2.stops);

	Query query5;
	ss = "BUSES_FOR_STOP Vnukovo";
	is.clear();
	is.str(ss);
	is >> query5;
	response = bm.GetBusesForStop(query5.stop);
	std::ostringstream os;
	os << response;
	
	std::string result {"32 32K\n"};
	assert(os.str() == result);
}

//---------------END-TEST-OF-CLASS-BUS-MANAGER-----------------------



void RunAllTests()
{
	testQuery_AllBuses_Operator_Input();
	testQuery_NewBus_Operator_Input();
	testQuery_BusesForStop_Operator_Input();
	testQuery_StopsForBus_Operator_Input();
	testRoutesCollector();
	testGetBusRoutesForStop();
	testBusManager_AddBus_StopsForBus();
	testBusManager_AllBuses();
	testBusManager_GetBusesForStop();
}






//---------------------END-OF-TESTS------------------------------



int main()
{
	int query_count;
	Query q;

	std::cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) 
	{
		std::cin >> q;
		switch (q.type) 	
		{
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				std::cout << bm.GetBusesForStop(q.stop) << std::endl;
				break;
			case QueryType::StopsForBus:
				std::cout << bm.GetStopsForBus(q.bus) << std::endl;
				break;
			case QueryType::AllBuses:
				std::cout << bm.GetAllBuses() << std::endl;
				break;
		}
	}

	RunAllTests();
	return 0;
}
