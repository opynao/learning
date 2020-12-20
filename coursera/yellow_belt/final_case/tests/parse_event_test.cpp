#include "parse_date_event.h"
#include "gtest/gtest.h"

#include <sstream>
#include <vector>
#include <string>

TEST( ParseEvent, SimpleEvent )
{
	std::istringstream is("event");
	EXPECT_EQ( ParseEvent(is), "event" );
}

TEST( ParseEvent, Parse_event_with_leading_spaces)
{
	std::istringstream is("   sport event ");
	EXPECT_EQ(ParseEvent(is), "sport event ");
}

TEST( ParseEvent, Parse_multiple_events )
{
	std::istringstream is("  first event  \n  second event");
	std::vector<std::string> events;
	events.push_back(ParseEvent(is));
	events.push_back(ParseEvent(is));
	std::vector<std::string> results {"first event  ", "second event"};
	EXPECT_EQ(events, results);
}
