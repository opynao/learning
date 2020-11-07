#include <cassert>
#include "../include/BusStops.h"

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

int main()
{
	RunAllTests();
	return 0;
}



