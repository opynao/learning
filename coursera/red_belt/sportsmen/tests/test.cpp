#include "sportsmen_list.h"
#include "parser.h"
#include "gtest/gtest.h"
#include <sstream>

TEST( SposrtsmenList, FinalTest )
{
  std::istringstream is("5\n42 0\n17 42\n13 0\n123 42\n5 13\n");
  std::ostringstream os;
  SportsmenList sp;
  Parser pr( is, os, sp );
  pr.Parse();
  EXPECT_EQ( os.str(), "17\n123\n42\n5\n13\n" );
}
