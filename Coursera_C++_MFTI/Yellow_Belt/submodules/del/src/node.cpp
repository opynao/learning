#include "node.h"
#include "condition_parser.h"


bool EmptyNode::Evaluate(Date& date, std::string& event) const 
{
  return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
  : cmp_{cmp}
  , date_{date}
{
}

bool DateComparisonNode::Evaluate(Date& date, std::string& event) const
{
  if (cmp_ == Comparison::Less)
    return date_ < date;
  else if (cmp_ == Comparison::LessOrEqual)
    return date_ <= date;
  else if (cmp_ == Comparison::Greater)
    return date_ > date;
  else if (cmp_ == Comparison::GreaterOrEqual)
    return date_ >= date;
  else if (cmp_ == Comparison::Equal)
    return date_ == date;
  else 
    return date_ != date;
}


EventComparisonNode::EventComparisonNode(const Comparison& cmp, const std::string& event)
  : cmp_{cmp}
  , event_{event}
{
}

bool EventComparisonNode::Evaluate(Date& date, std::string& event) const
{
  else if (cmp_ == Comparison::Equal)
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
 
bool LogicalOperationNode::Evaluate(Date& date, Event_t& event) const override
{
  if( lo_ == LogicalOperation::AND )
    return rhs_->Evaluate && lhs_->Evaluate;
  return rhs_->Evaluate || lhs_->Evaluate;
}

