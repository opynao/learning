#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <functional>

void Test1();
void Test2();
void Test3();

namespace Utils
{
    template <typename T>
    bool IsSameSign(T lhs, T rhs)
    {
        return (lhs >= 0 && rhs >= 0) || (lhs < 0 && rhs < 0);
    }
} //!namespace Utils

namespace ParkingSystem
{
    class MaxDistanceToNearestUsedRackAlgorithm
    {
    public:
        MaxDistanceToNearestUsedRackAlgorithm(std::vector<int> vUsedRacks)
            : vUsedRacks_{std::move(vUsedRacks)}
            , pos_ { std::cbegin(vUsedRacks_)}
        {
        }

        int operator()()
        {
            Sort();
            return GetMaxDistanceBetweenUsedRacks() / 2;
        }

    private:
        void Sort()
        {
            std::sort(vUsedRacks_.begin(), vUsedRacks_.end());
        }
        
        int GetMaxDistanceBetweenUsedRacks()
        {
            std::for_each(vUsedRacks_.cbegin(), std::prev(vUsedRacks_.cend()),
                                 [this](int rackNumber) {
                                     return CalculateMaxDistance(rackNumber);
                                 });

            return nMaxDistanceBetweenUsedRacks_;
        }
        int CalculateMaxDistance(int rackNumber)
        {
            return nMaxDistanceBetweenUsedRacks_ = std::max(nMaxDistanceBetweenUsedRacks_, CalculateDistanceToNextRack(rackNumber));
        }
        int CalculateDistanceToNextRack(int rackNumber)
        {
            ++pos_;
            const auto nextRackNumber = *pos_;
            if (Utils::IsSameSign(rackNumber, nextRackNumber))
                return (std::abs((rackNumber - nextRackNumber)));
            return (std::abs(rackNumber) + std::abs(nextRackNumber));
        }

    private:
        std::vector<int> vUsedRacks_;
        std::vector<int>::const_iterator pos_;
        int nMaxDistanceBetweenUsedRacks_{};
    };
} //!namespace ParkingSystem

void Test1()
{
    assert(2 == ParkingSystem::MaxDistanceToNearestUsedRackAlgorithm({5, 1, 8, -7, -2})());
}

void Test2()
{
    assert(0 == ParkingSystem::MaxDistanceToNearestUsedRackAlgorithm({5, 5})());
}

void Test3()
{
    assert(2 == ParkingSystem::MaxDistanceToNearestUsedRackAlgorithm({10, 0, 8, 2, -1, 12, 11, 3})());
}

int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}
