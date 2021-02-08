#include "http_request.h"
#include "stats.h"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#define PR(x) std::cerr << #x << " = " << x << std::endl
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

Stats::Stats()
{
  for( auto& method : storage_methods_ )
    methods_[method] = 0;
  
  for( auto& uri : storage_uris_ )
    uris_[ uri ] = 0;
}
void Stats::AddMethod(std::string_view method)
{
  auto it = std::find( storage_methods_.begin(), storage_methods_.end(), method );
  if( it == storage_methods_.cend() )
  {
    ++methods_[ storage_methods_.back() ];
    return;
  }
  ++methods_[ *it ];
}

void Stats::AddUri(std::string_view uri)
{
  auto it = std::find( storage_uris_.begin(), storage_uris_.end(), uri );
  if( it == storage_uris_.cend() )
  {
    ++uris_[ storage_uris_.back() ];
    return;
  }
  ++uris_[ *it ];
}

const std::map<std::string_view, int>& Stats::GetMethodStats() const
{
  return methods_;
}

const std::map<std::string_view, int>& Stats::GetUriStats() const
{
  return uris_;
}


std::deque< std::string > SplitIntoWords( const std::string& str ) 
{
  std::deque< std::string > result;
  size_t pos = str.find_first_not_of(' ');
  const size_t pos_end = str.npos;
  
  while(true) 
  {
    size_t space = str.find(' ', pos);
    result.push_back( space == pos_end ? str.substr(pos): str.substr(pos, space - pos));
    if( space == pos_end )
      break;
    else
      pos = space + 1;
  }
  return result;
}


HttpRequest ParseRequest(std::string_view str)
{
  HttpRequest hr;
  static std::deque< std::string > buffer;
  for( auto& item : SplitIntoWords( std::string(str) ) )
    buffer.push_back( item );
  hr.method = *std::prev( buffer.end(), 3 );
  hr.uri = *std::prev( buffer.end(), 2 );
  hr.protocol = *std::prev( buffer.end() );
  return hr;
}
