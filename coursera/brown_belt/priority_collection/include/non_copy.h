#pragma once

#include <string>

class StringNonCopyable : public std::string 
{
public:
  using std::string::string;  

  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};


