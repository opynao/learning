#pragma once
#include "reading_manager.h"
#include <iostream>
#include <string>
#include <map>

#ifdef ETALON
class Parser
{
public:
  Parser( std::istream& is, std::ostream& os, ReadingManager& rm)
    : m_is {is}
    , m_os {os}
    , manager {rm}
  {}
  void Parse();
private:
  std::istream& m_is;
  std::ostream& m_os;
  ReadingManager manager;
};
#endif


#ifndef ETALON
enum class QueryType
{
  READ,
  CHEER
};

class Parser
{
public:
  Parser( std::istream& is, std::ostream& os, ReadingManager& rm)
    : m_is {is}
    , m_os {os}
    , m_rm {rm}
  {}
  void Parse();
  void MakeQuery();
private:
  std::istream& m_is;
  std::ostream& m_os;
  ReadingManager m_rm;
  std::map< std::string, QueryType > m
  {
    { "READ", QueryType::READ },
    { "CHEER", QueryType::CHEER }
  };
};
#endif
