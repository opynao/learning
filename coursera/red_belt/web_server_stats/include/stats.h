#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

class Stats 
{
public:
  using Stats_t = std::map<std::string_view, int>;

public:
  void AddMethod(std::string_view method);
  void AddUri(std::string_view uri);
  const Stats_t& GetMethodStats() const;
  const Stats_t& GetUriStats() const;

private:
  void Add(std::string_view s, Stats_t m);

private:
  Stats_t methods_;
  Stats_t uris_;
//  std::deque< std::string > storage_;
};

HttpRequest ParseRequest(std::string_view line);
