#pragma once
#include <unordered_map>
#include <set>

class ReadingManager 
{
public:
  using UserID = size_t;
  using PageNumber = size_t;
public:
  void Read(int user_id, int page_count); 
  double Cheer(int user_id) const;
private:
  std::unordered_map< UserID, PageNumber > m_UsersPages;
  std::multiset< PageNumber > m_Pages;
};


