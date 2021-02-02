#pragma once
#include <optional>

class Request
{
public:
  virtual ~Request() {}
  virtual std::optional< size_t > GetAnswer() const = 0;
  virtual void SetAnswer(const size_t) = 0;
};
