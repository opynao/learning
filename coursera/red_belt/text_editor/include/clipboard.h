#pragma once
#include <string_view>
#include <string>

class Clipboard
{
public:
  void Save( const char* ch, const size_t tokens )
  {
    view_ = std::string_view( ch, tokens );  
  }
  void Load()
  {
    str_ = std::string( view_ );
  }
  std::string Get() const 
  { 
    if( str_.empty() )
      return std::string( view_ );
    return str_;
  }
  void Clear()
  {
    str_.clear();
    view_ = {};
  }
  bool Empty()
  {
    return view_.empty();
  }
  size_t Size()
  {
    return view_.size();
  }
private:
  std::string_view view_;
  std::string str_;
};
