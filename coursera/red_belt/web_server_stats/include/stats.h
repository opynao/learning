#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <string>
#include <deque>

class Stats 
{
public:
  using Stats_t = std::map< std::string_view, int >;

public:
  Stats();
  void AddMethod(std::string_view method);
  void AddUri(std::string_view uri);
  const Stats_t& GetMethodStats() const;
  const Stats_t& GetUriStats() const;

private:
  Stats_t methods_ {};
  Stats_t uris_ {};

private:
  const std::deque< std::string > storage_methods_
  {
    "GET",
    "POST",
    "PUT",
    "DELETE",
    "UNKNOWN"
  };
  const std::deque< std::string > storage_uris_
  {
    "/", 
    "/order", 
    "/product", 
    "/basket", 
    "/help",
    "unknown"
  };
};

HttpRequest ParseRequest(std::string_view line);
