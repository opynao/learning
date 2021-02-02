#pragma once
#include <map>
#include <set>
#include <array>
#include <vector>
#include <iostream>
#define LOGF std::cerr<<__FUNCTION__ <<" : " <<__LINE__<<std::endl
#define LOGVAL(val) std::cerr << #val <<  " = " << val << ";" << std::endl

using namespace std;

//#define ETALON  
#ifndef ETALON

class ReadingManager 
{
public:
  using UserID = size_t;
  using PageNumber = size_t;
  using UserCount = size_t;
public:
  void Read(int user_id, int page_count); 
  double Cheer(int user_id) const;
private:
  std::array< PageNumber, 100'000 > m_UsersPages;
  std::array< UserCount, 1000 > m_PageUsers;
  std::set< UserID > m_Users;
};
#endif

#ifdef ETALON
class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
      AddUser(user_id);
    }
    user_page_counts_[user_id] = page_count;
    int& position = user_positions_[user_id];
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
      SwapUsers(position, position - 1);
    }
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];
    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
        return 0;
    }
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return (user_count - position) * 1.0 / (user_count - 1);
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
  vector<int> user_positions_; // позиции в векторе sorted_users_

  int GetUserCount() const {
    return sorted_users_.size();
  }
  void AddUser(int user_id) {
    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
  }
  void SwapUsers(int lhs_position, int rhs_position) {
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
};


#endif
