#pragma once
#include <string_view>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <set>
#define LOGF std::cerr<< __FUNCTION__ << " " << __LINE__ << std::endl

class Translator 
{
public:
  using Translator_t = std::map< std::string_view, std::string_view >;

public:  
  void Add(const std::string_view& source, const std::string_view& target);
  std::string_view TranslateForward(const std::string_view& source) const;
  std::string_view TranslateBackward(const std::string_view& target) const;

private:
  std::string_view GetCache( const std::string_view& str );
  std::string_view Translate( const Translator_t& m, const std::string_view& str ) const;

private:
  Translator_t forward_translation {};
  Translator_t backward_translation {};
  std::set<std::string> cache;
};


