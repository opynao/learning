#pragma once

#include <string_view>

struct HttpRequest 
{
  std::string_view method;
  std::string_view uri;
  std::string_view protocol;
};
