#include "node.h"
#include "condition_parser.h"

#include <iostream>
#define LOGF ;
//std::cerr<< __FUNCTION__ <<std::endl 

bool EmptyNode::Evaluate([[maybe_unused]] const Date& date, [[maybe_unused]] const Event_t& event) const 
{
  return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
  : cmp_{cmp}
  , date_{date}
{
  LOGF;
}

bool DateComparisonNode::Evaluate(const Date& date, [[maybe_unused]] const Event_t& event) const
{
  LOGF;
  if( cmp_ ==  Comparison::Less )
    return date_ < date;
  else if( cmp_ == Comparison::LessOrEqual )
    return date_ < date || date_ == date;
  else if( cmp_ == Comparison::Greater )
    return !(date_ < date);
  else if( cmp_ == Comparison::GreaterOrEqual )
    return !(date_ < date) || date_ == date;
  else if( cmp_ == Comparison::Equal )
    return date_ == date;
  return !(date_ == date);
}


EventComparisonNode::EventComparisonNode(const Comparison& cmp, const Event_t& event)
  : cmp_{cmp}
  , event_{event}
{
}

bool EventComparisonNode::Evaluate([[maybe_unused]] const Date& date, const Event_t& event) const
{
  if (cmp_ == Comparison::Equal)
    return event_ == event;
  else
    return event_ != event;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& lo, const std::shared_ptr<Node>& rhs, const std::shared_ptr<Node>& lhs)
  : lo_ {lo}
  , rhs_ {rhs}
  , lhs_ {lhs}
{  
} 
 
bool LogicalOperationNode::Evaluate(const Date& date, const Event_t& event) const 
{
  LOGF;
  if( lo_ == LogicalOperation::And )
    return rhs_->Evaluate(date, event) && lhs_->Evaluate(date, event);
  return rhs_->Evaluate(date, event) || lhs_->Evaluate(date, event);
}

