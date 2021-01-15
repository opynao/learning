#include <list>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>


class SportsmenList
{
public:
  using SportsmenRow_t = std::list< size_t >;

public:
  SportsmenList()
    : it_( MAX_ATHLETES + 1, row.end() )
  {}
  void Add( const size_t sportsmen, const size_t next_sportsmen );
  const SportsmenRow_t& Get() const;

private:
  static const size_t MAX_ATHLETES {100'000};
  SportsmenRow_t row;
  std::vector< SportsmenRow_t::iterator > it_;
};

class Parser
{
public:
  Parser(std::istream& is, std::ostream& os, SportsmenList& sp);  
  void Parse(); 

private:
  void PrintList();

private:
  std::istream& is_;
  std::ostream& os_;
  SportsmenList& row;
};

void SportsmenList::Add( const size_t sportsmen, const size_t next_sportsmen )
{
  it_[sportsmen] = row.insert( it_[next_sportsmen], sportsmen );
}

const SportsmenList::SportsmenRow_t& SportsmenList::Get() const
{
  return row;
}

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
    size_t toAdd {};
    size_t afterWhichToAdd {};
    is_ >> toAdd;
    is_ >> afterWhichToAdd;
    row.Add( toAdd, afterWhichToAdd );
  }
  PrintList();
}

void Parser::PrintList()
{
  for( const auto& sportsmen : row.Get() )
    os_ << sportsmen << "\n";
}

int main()
{
  SportsmenList sp;
  Parser pr( std::cin, std::cout, sp );
  pr.Parse();
  return 0;
}
