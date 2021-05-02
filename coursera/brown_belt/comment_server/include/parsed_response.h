#pragma once
#include "http_header.h"

#include <vector>
#include <string>
#include <istream>

struct ParsedResponse
{
  ParsedResponse() = default;
  ParsedResponse(const int code_)
      : code{code_}
  {
  }
  ParsedResponse(const int code_,
                 const std::vector<HttpHeader> &headers_,
                 const std::string &content_)
      : code{code_}, headers{headers_}, content{content_}
  {
  }
  int code{};
  std::vector<HttpHeader> headers{};
  std::string content{};
};

std::istream &operator>>(std::istream &input, ParsedResponse &r);