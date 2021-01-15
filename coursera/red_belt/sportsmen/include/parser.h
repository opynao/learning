#pragma once
#include <iostream>
#include "sportsmen_list.h"

class Parser
{
public:
  Parser(std::istream& is, std::ostream& os, SportsmenList& sp);  
  void Parse(); 

private:
  void PrintList();

private:
  std::istream& is_;
  std::ostream& os_;
  SportsmenList& row;
};

