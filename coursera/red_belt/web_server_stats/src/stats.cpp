#include "http_request.h"
#include "stats.h"
#include <iostream>
#include <vector>
#include <deque>

void Stats::AddMethod(std::string_view method)
{
  Add( method, methods_ );
}

void Stats::AddUri(std::string_view uri)
{
  Add( uri, uris_ );
}

void Stats::Add(std::string_view s, Stats_t m)
{
  auto it = m.find(s);
  if( it == m.cend() )
  {
    m[s] = 1;
    return;
  }
  ++it->second;
}

const std::map<std::string_view, int>& Stats::GetMethodStats() const
{
//  std::cerr << methods_.size() << std::endl;
  return methods_;
}

const std::map<std::string_view, int>& Stats::GetUriStats() const
{
//  std::cerr << uris_.size() << std::endl;
  return uris_;
}

std::vector<std::string_view> SplitIntoWordsView ( const std::string_view& str ) 
{
  std::vector<std::string_view> result;
  size_t pos = 0;
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
  const auto& result = SplitIntoWordsView( str );
//  for( const auto& i : result )
//    std::cerr << i << std::endl;
  hr.method {result[0]);
  hr.uri = result[1];
  hr.protocol = result[2];
//  std::cerr << hr.method << hr.uri << hr.protocol << std::endl;
//  std::cerr << str << std::endl;
  return hr;
}
