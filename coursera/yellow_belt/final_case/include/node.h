#pragma once

#include "date.h"

#include <string>
#include <memory>
#include <map>
#include <functional>
using Event_t = std::string;

enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation
{
   Or, 
   And
};


class Node
{
public:
  virtual bool Evaluate(const Date&, const Event_t&) const = 0;
};

class EmptyNode : public Node
{
public:
  virtual bool Evaluate(const Date&, const Event_t&) const override;
};

class DateComparisonNode : public Node
{
public:
  DateComparisonNode(const Comparison&, const Date&);
  virtual bool Evaluate(const Date&, const Event_t&) const override;
private:
  Comparison cmp_;
  Date date_;
};


class EventComparisonNode : public Node
{
public:
  EventComparisonNode(const Comparison&, const std::string&);
  virtual bool Evaluate(const Date&, const Event_t&) const override;
private:
  Comparison cmp_;
  std::string event_;
};

class LogicalOperationNode : public Node
{
public:
  LogicalOperationNode(const LogicalOperation&, const std::shared_ptr<Node>&, const std::shared_ptr<Node>&);
  virtual bool Evaluate(const Date&, const Event_t&) const override;
private:
  LogicalOperation lo_;
  std::shared_ptr<Node> lhs_;
  std::shared_ptr<Node> rhs_;
};
