#include "stack_vector.h"
#include "profile.h"

#include <random>
#include <stdexcept>
#include <iostream>

using namespace std;


void TestVectorWithoutReserve(const std::vector<std::vector<int>>& test_data)
{
  {
    LOG_DURATION("vector w/o reserve");
    for (auto& cur_vec : test_data) 
    {
      vector<int> v;
      for (const int& x : cur_vec)
        v.push_back(x);
    }
  }
}

void TestVectorWithReserve(const std::vector<std::vector<int>>& test_data)
{
 {
    LOG_DURATION("vector with reserve");
    for (auto& cur_vec : test_data) 
    {
      vector<int> v;
      v.reserve(cur_vec.size());
      for (const int& x : cur_vec)
        v.push_back(x);
    }
  }
}

void TestStackVector(const std::vector<std::vector<int>>& test_data)
{
  const size_t max_size = 2500;
 {
    LOG_DURATION("StackVector");
    for (auto& cur_vec : test_data)
    {
      StackVector<int, max_size> v;
      for (const int& x : cur_vec)
        v.PushBack(x);
    }
  }
}

int main() 
{
  cerr << "Running benchmark..." << endl;
  const size_t max_size = 2500;

  default_random_engine re;
  uniform_int_distribution<int> value_gen(1, max_size);


  vector<vector<int>> test_data(50000);
  for (auto& cur_vec : test_data) 
  {
    cur_vec.resize(value_gen(re));
    for (int& x : cur_vec)
      x = value_gen(re);
  }

  TestVectorWithoutReserve(test_data);
  TestVectorWithReserve(test_data); 
  TestStackVector(test_data);
  cerr << "Done" << endl;
}
