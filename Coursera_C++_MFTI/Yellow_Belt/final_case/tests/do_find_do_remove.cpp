#include "parse_date_event.h"
#include "database.h"
#include "node.h"
#include "do_find_do_remove.h"
#include "condition_parser.h"
#include "gtest/gtest.h"

#include <vector>
#include <string>
#include <utility>
#include <sstream>


int DoRemove (Database& db, const std::string& str) 
{
  std::istringstream is (str);
  auto condition = ParseCondition(is);
  auto predicate = [condition](const Date &date, const std::string &event) { return condition->Evaluate(date, event); };
  return db.RemoveIf(predicate);
}

std::string DoFind (Database& db, const std::string& str) 
{
  std::istringstream is (str);
  auto condition = ParseCondition(is);
  auto predicate = [condition](const Date &date, const std::string &event) { return condition->Evaluate(date, event); };
  const auto entries = db.FindIf(predicate);
  std::ostringstream os;
  for (const auto& entry : entries) 
  {
     os << entry << std::endl;
  }
  os << entries.size();
  return os.str();
}


