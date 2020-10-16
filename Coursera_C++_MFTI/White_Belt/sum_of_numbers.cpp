#include <numeric>
#include <iostream>
#include <array>
#include <algorithm>

using Numbers = std::array<int,2>;

int main()
{
	Numbers arNumbers;
	std::for_each(arNumbers.begin(), arNumbers.end(), [](Numbers::reference rVal) {std::cin >>rVal;});
	std::cout << std::accumulate(arNumbers.cbegin(), arNumbers.cend(),0);	
	return 0;
}

