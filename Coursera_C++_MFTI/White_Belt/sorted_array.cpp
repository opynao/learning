#include <cstdlib>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

int main()
{
	size_t arraySize {};
	std::cin >> arraySize;

	std::vector<int> vInts {};
	vInts.reserve(arraySize);
	std::copy(std::istream_iterator<int>(std::cin),std::istream_iterator<int>(),std::back_inserter(vInts));
	std::sort(std::begin(vInts), std::end(vInts),[]( int x, int y ) -> bool { return std::abs(x) < std::abs(y); });
	std::copy(std::cbegin(vInts), std::cend(vInts), std::ostream_iterator<int>(std::cout," "));
	return 0;
}
