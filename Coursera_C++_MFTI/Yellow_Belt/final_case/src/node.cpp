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
}

bool DateComparisonNode::Evaluate(const Date& date, [[maybe_unused]] const Event_t& event) const
{
  LOGF;
  if( cmp_ ==  Comparison::Less )
    return date < date_;

  else if( cmp_ == Comparison::LessOrEqual )
    return date <= date_;
  
  else if( cmp_ == Comparison::Greater )
    return date > date_;
  
  else if( cmp_ == Comparison::GreaterOrEqual )
    return date >= date_;
  
  else if( cmp_ == Comparison::Equal )
    return date_ == date;
  
  else if( cmp_ == Comparison::NotEqual )  
    return date_ != date;
  else 
    return true;
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

