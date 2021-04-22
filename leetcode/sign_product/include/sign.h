#pragma once
#include <algorithm>
#include <vector>
#include <iostream>

class ProductSign
{
public:
    int arraySign(const std::vector<int> &nums)
    {
        int result{1};
        std::for_each(nums.cbegin(), nums.cend(), [&result](const int num) { 
            if(num > 0)
                return result *= 1;
            else if(num < 0)
                return result *= (-1);
            else
                return result = 0; });
        return result;
    }
};