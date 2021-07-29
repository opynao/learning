#pragma once
#include <vector>
#include <algorithm>

class Solution
{
public:
    int removeDuplicates(std::vector<int> &nums)
    {
        int prevNum{};
        std::for_each(nums.begin(), nums.end(),
                      [&prevNum, &nums](int num) mutable {
                          if (num == prevNum)
                              nums.erase(num);
                      });
    }
};