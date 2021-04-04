#pragma once

#include <deque>
#include <cstdint>
#include <list>
#include <vector>
#include <set>

const int MINUTES_IN_DAY = 86400;

class ClientData
{
public:  
  using time_t = int64_t;
  using client_t = int;

public:
  void Pop();

  void Push( time_t time, client_t clientId );

  int GetClientsSize( time_t time );

private:
  std::deque< time_t > time_;
  std::deque< client_t > clientId_;
  std::multiset< client_t > clients_;
  size_t count {};
};
