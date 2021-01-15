#include "stack_vector.h"
#include "profile.h"

#include <random>
#include <stdexcept>
#include <iostream>

using namespace std;

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

  {
    LOG_DURATION("vector w/o reserve");
    for (auto& cur_vec : test_data) 
    {
      vector<int> v;
      for (int x : cur_vec)
        v.push_back(x);
    }
  }
  {
    LOG_DURATION("vector with reserve");
    for (auto& cur_vec : test_data) 
    {
      vector<int> v;
      v.reserve(cur_vec.size());
      for (int x : cur_vec)
        v.push_back(x);
    }
  }
  {
    LOG_DURATION("StackVector");
    for (auto& cur_vec : test_data)
    {
      StackVector<int, max_size> v;
      for (int x : cur_vec)
        v.PushBack(x);
    }
  }
  cerr << "Done" << endl;
}
