
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

template <typename String>
using Group = std::vector<String>;

template <typename String>
std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings) 
{
  using Char = typename String::value_type;
  
  std::vector< Group< String >> v;
  std::map< std::set< Char >, Group< String >> unique_chars;
  
  for( auto& str : strings )
  {
    std::set< Char > s;
    std::copy( std::begin(str), std::end(str), std::inserter( s, s.end() ) );
    unique_chars[std::move(s)].push_back( std::move( str) );
  }
  std::for_each( std::begin( unique_chars ), std::end( unique_chars ), [&v]( auto& pr ) { v.push_back( std::move( pr.second) ); }  ); 
  
  return v;
}

int main()
{
	return 0;
}
