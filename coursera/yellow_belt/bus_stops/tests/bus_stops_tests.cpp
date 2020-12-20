#include <cassert>
#include "gtest/gtest.h"
#include "bus_manager.h"
#include "query.h"
#include "responses.h"
#define LOGF std::cerr << __FUNCTION__ << std::endl


class QueryTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	Query query;
	std::istringstream is;
	std::ostringstream os;
};


class BusManagerTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	Query query;
	std::istringstream is;
	std::ostringstream os;
	BusManager bm;
};


//---------------Query---------------------

TEST_F( QueryTest, AllBuses_Operator_Input )
{
	std::string ss {"ALL_BUSES"};
	is.str(ss);
	is >> query;
	EXPECT_EQ( query.type, QueryType::AllBuses );
}

TEST_F( QueryTest, NewBus_Operator_Input )
{
	std::string ss {"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"};
	is.str(ss);
	is >> query;
	stops_t result {"Tolstopaltsevo","Marushkino", "Vnukovo"};
	EXPECT_EQ( query.type, QueryType::NewBus );
	EXPECT_EQ( query.bus, "32" );
	EXPECT_EQ( query.stops.size(), 3 );
	EXPECT_EQ( query.stops, result );
}

TEST_F( QueryTest, AddingTwoString )
{
	BusManager bm;
	StopsForBusResponse response;
	std::string ss = "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo";
	is.str(ss);
	is >> query;
	bm.AddBus(query.bus,query.stops);

	ss = "STOPS_FOR_BUS 272";
	is.clear();
	is.str(ss);
	is >> query;
	response = bm.GetStopsForBus(query.bus);
	os << response;
	std::string result {"Stop Vnukovo: no interchange\nStop Moskovsky: no interchange\nStop Rumyantsevo: no interchange\nStop Troparyovo: no interchange\n"};

	EXPECT_EQ( os.str(), result );

}

TEST_F( QueryTest, BusesForStop_Operator_Input )
{
	std::string ss {"BUSES_FOR_STOP Vnukovo"};
	is.str(ss);
	is >> query;
	EXPECT_EQ( query.type, QueryType::BusesForStop );
	EXPECT_EQ( query.stop, "Vnukovo" );
}

TEST_F( QueryTest, StopsForBus_Operator_Input )
{
	std::string ss {"STOPS_FOR_BUS 32K"};
	is.str(ss);
	is >> query;
	EXPECT_EQ( query.type, QueryType::StopsForBus );
	EXPECT_EQ( query.bus, "32K" );
}

//-------------------BusManager----------------------------

TEST_F( BusManagerTest, GetStopsForBus )
{
	StopsForBusResponse response;
	for( const auto& cmd : std::vector<std::string> {{"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"}, 
				{"NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo"},
				{"NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo"},
				{"NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo"}})
	{
		is.str(cmd);
		is >> query;
		bm.AddBus(query.bus, query.stops);
		is.clear();
	}
	
	std::string ss = "STOPS_FOR_BUS 272";
	is.str(ss);
	is >> query;
	response = bm.GetStopsForBus(query.bus);
	os << response;
	std::string result {"Stop Vnukovo: 32 32K 950\nStop Moskovsky: no interchange\nStop Rumyantsevo: no interchange\nStop Troparyovo: 950\n"};

	EXPECT_EQ( os.str(), result );
}

TEST_F( BusManagerTest, GetBusRoutesForStop )
{
	for( const auto& cmd : std::vector<std::string> {{"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"}, 
				{"NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo"},
				{"NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo"}})
	{
		is.str(cmd);
		is >> query;
		bm.AddBus(query.bus, query.stops);
		is.clear();
	}

	routes_t result {"32","32K","950"};
	
	routes_t out = bm.GetBusRoutesForStop("Vnukovo");

	EXPECT_EQ( out, result );
}

TEST_F( BusManagerTest, GetBusRoutesForStopPrintInRightOrder )
{
	for( const auto& cmd : std::vector<std::string> {{"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"}, 
				{"NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo"},
				{"NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo"},
				{"NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo"}})
	{
		is.str(cmd);
		is >> query;
		bm.AddBus(query.bus, query.stops);
		is.clear();
	}

	routes_t result {"32","32K","950","272"};
	
	routes_t out = bm.GetBusRoutesForStop("Vnukovo");

	EXPECT_EQ( out, result );
}


TEST_F( BusManagerTest, AllBuses )
{
	AllBusesResponse response;
	for( const auto& cmd : std::vector<std::string> {{"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"}, 
				{"NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo"},
				{"NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo"},
				{"NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo"}})
	{
		is.str(cmd);
		is >> query;
		bm.AddBus(query.bus, query.stops);
		is.clear();
	}

	std::string ss = "ALL_BUSES";
	is.str(ss);
	is >> query;
	response = bm.GetAllBuses();
	os << response;

	std::string result {"Bus 272: Vnukovo Moskovsky Rumyantsevo Troparyovo\nBus 32: Tolstopaltsevo Marushkino Vnukovo\nBus 32K: Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo\nBus 950: Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo\n"};

	EXPECT_EQ( os.str(), result );
}

TEST_F( BusManagerTest, GetBusesForStop )
{
	BusesForStopResponse response;
	for( const auto& cmd : std::vector<std::string> {{"NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"}, 
				{"NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo"}})
	{
		is.str(cmd);
		is >> query;
		bm.AddBus(query.bus, query.stops);
		is.clear();
	}
 	std::string ss = "BUSES_FOR_STOP Vnukovo";
	is.str(ss);
	is >> query;
	response = bm.GetBusesForStop(query.stop);
	os << response;
	std::string result {"32 32K\n"};
	
	EXPECT_EQ( os.str(), result );
}


TEST( RoutesCollector, AddingElems )
{
	RoutesCollector routes("Vnukovo");
	busInfo_t busFirst { {"32", {"Tolstopaltsevo","Marushkino", "Vnukovo"}} };
	routes_t result {"32"};
	routes(*busFirst.begin());
	EXPECT_EQ( result, routes.GetRoutes() );

	busFirst.emplace( "44",std::vector<std::string> {"a","b","Vnukovo"} );
	result.push_back("44");
	routes(*std::next(busFirst.begin()));
	EXPECT_EQ( result, routes.GetRoutes() );
}

class PrintStopsForBusTest : public ::testing::Test
{
protected:
	void SetUp() override
	{}
	std::ostringstream os;
	StopsForBusResponse r;	
};

TEST_F( PrintStopsForBusTest, NoBusesForStop_NoInterchange )
{
	r.stops = { { {"Vnukovo", {}} }, {"Vnukovo"} };
	PrintStopsForBus(os,r);
	std::string result {"Stop Vnukovo: no interchange\n"};
	EXPECT_EQ(os.str(), result);	
}

TEST_F( PrintStopsForBusTest, ThereAreBusesForStop )
{
	r.stops = { { {"Vnukovo", {"12","34","34K"}} }, {"Vnukovo"} };
	PrintStopsForBus(os,r);
	std::string result {"Stop Vnukovo: 12 34 34K\n"};
	EXPECT_EQ(os.str(), result);	
}

TEST_F( PrintStopsForBusTest, ThereAreBusesForStops )
{
	r.stops = { 
			{ 
				{"Vnukovo", {"12","34","34K"}},
				{"Kreml", {"34","57"}} 
			}, 
			{"Vnukovo", "Kreml"} 
		  };
	PrintStopsForBus(os,r);
	std::string result {"Stop Vnukovo: 12 34 34K\nStop Kreml: 34 57\n"};
	EXPECT_EQ(os.str(), result);	
}

TEST_F( PrintStopsForBusTest, ThereAreBusesForStops_ )
{
	r.stops = { 
			{ 
				{"Vnukovo", {"12","34","34K"}},
				{"Kreml", {"34","57"}} 
			}, 
			{"Kreml", "Vnukovo"} 
		  };
	PrintStopsForBus(os,r);
	std::string result {"Stop Kreml: 34 57\nStop Vnukovo: 12 34 34K\n"};
	EXPECT_EQ(os.str(), result);	
}
