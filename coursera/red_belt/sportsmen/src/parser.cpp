#include "parser.h"

Parser::Parser(std::istream& is, std::ostream& os, SportsmenList& sp)
  : is_ {is}
  , os_ {os}
  , row {sp}
  {}

void Parser::Parse()
{
  size_t sportsmenQuantity {};
  is_ >> sportsmenQuantity;
  while( sportsmenQuantity-- )
  {
    size_t sportsmen {};
    size_t next_sportsmen {};
    is_ >> sportsmen;
    is_ >> next_sportsmen;
    row.Add( sportsmen, next_sportsmen );
  }
  PrintList();
}

void Parser::PrintList()
{
  for( const auto& sportsmen : row.Get() )
    os_ << sportsmen << "\n";
}

