#include "node.h"
#include "condition_parser.h"

#include <iostream>
#define LOGF ;
//std::cerr<< __FUNCTION__ <<std::endl 

namespace
{
  template <typename T>
  bool Compare(const Comparison cmp, T left, T right)
  {
    if( cmp ==  Comparison::Less )
      return left < right;

    if( cmp == Comparison::LessOrEqual )
      return left <= right;
    
    if( cmp == Comparison::Greater )
      return left > right;
    
    if( cmp == Comparison::GreaterOrEqual )
      return left >= right;
    
    if( cmp == Comparison::Equal )
      return left == right;
    
    if( cmp == Comparison::NotEqual )  
      return left != right;
    
    return true;
  }
}

bool EmptyNode::Evaluate([[maybe_unused]] const Date& date, [[maybe_unused]] const Event_t& event) const 
{
  return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
  : cmp_{cmp}
  , date_{date}
{
}

bool DateComparisonNode::Evaluate(const Date& date, [[maybe_unused]] const Event_t& event) const
{
  return Compare(cmp_, date, date_);
}


EventComparisonNode::EventComparisonNode(const Comparison& cmp, const Event_t& event)
  : cmp_{cmp}
  , event_{event}
{
}


bool EventComparisonNode::Evaluate([[maybe_unused]] const Date& date, const Event_t& event) const
{
  return Compare(cmp_, event, event_);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& lo, const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs)
  : lo_ {lo}
  , lhs_ {lhs}
  , rhs_ {rhs}
{  
} 
 
bool LogicalOperationNode::Evaluate(const Date& date, const Event_t& event) const 
{
  LOGF;
  if( lo_ == LogicalOperation::And )
    return lhs_->Evaluate(date, event) && rhs_->Evaluate(date, event);
  else if ( lo_ == LogicalOperation::Or )
    return lhs_->Evaluate(date, event) || rhs_->Evaluate(date, event);
  return true;
}

