#pragma once
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#define LOGF //std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl
#include <list>

class Editor
{
 public:
  Editor();

  void Left();
  
  void Right();
  
  void Insert(char token);
 
  void Cut(size_t tokens = 1);
  
  void Copy(size_t tokens = 1);
  
  void Paste();
  
  std::string GetText() const; 

private:
  size_t GetRealTokenSize(size_t tokens);

private:
  std::list< char > str_ {};
  std::list< char >::iterator current_it_;
  std::list< char > clipboard_ {};
  size_t current_position_ {};
};

void TypeText(Editor& editor, const std::string& text);
