#include "two_sum.h"
#include <algorithm>
#include <iterator>

std::vector<int> TwoSum::FindPos(std::vector<int> &nums, int target)
{
    std::vector<int> result{};
    result.reserve(2);
    int firstTerm{};
    for (auto it = nums.begin(); it != nums.cend(); ++it)
    {
        firstTerm = target - *it;
        auto itFind = std::find(std::next(it), nums.end(), firstTerm);
        if (itFind == nums.cend())
            continue;
        else
        {
            size_t distanceFirst = std::distance(nums.begin(), it);
            size_t distanceSecond = std::distance(nums.begin(), itFind);
            result.push_back(distanceFirst);
            result.push_back(distanceSecond);
        }
    }
    return result;
}
