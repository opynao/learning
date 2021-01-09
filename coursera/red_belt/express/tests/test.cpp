#include "route_manager.h"
#include "parser.h"
#include "gtest/gtest.h"
#include <sstream>

class RouteManagerTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }
 RouteManager routes;
 std::ostringstream os;
};

TEST_F( RouteManagerTest, ComplexTest )
{
  std::istringstream is("7\nADD -2 5\nADD 10 4\nADD 5 8\nGO 4 10\nGO 4 -2\nGO 5 0\nGO 5 100");
  Parser pr( is, os, routes );
  pr.Parse();
  EXPECT_EQ( os.str(), "0\n6\n2\n92\n" );
}

TEST_F( RouteManagerTest, ThereIsNoRouteInDB )
{
  std::istringstream is("2\nADD 4 0\nGO 5 0");
  Parser pr( is, os, routes );
  pr.Parse();
  EXPECT_EQ( os.str(), "5\n" );
}

TEST_F( RouteManagerTest, ThereIsTheSameRouteInDB )
{
  std::istringstream is("2\nADD 4 0\nGO 4 0");
  Parser pr( is, os, routes );
  pr.Parse();
  EXPECT_EQ( os.str(), "0\n" );
}

TEST_F( RouteManagerTest, ThereIsOneRouteInDB_ButReverse )
{
  std::istringstream is("2\nADD 4 0\nGO 4 5");
  Parser pr( is, os, routes );
  pr.Parse();
  EXPECT_EQ( os.str(), "1\n" );
}

TEST_F( RouteManagerTest, ThereIsOneRouteInDB )
{
  std::istringstream is("2\nADD 4 0\nGO 4 -1");
  Parser pr( is, os, routes );
  pr.Parse();
  EXPECT_EQ( os.str(), "1\n" );
}
