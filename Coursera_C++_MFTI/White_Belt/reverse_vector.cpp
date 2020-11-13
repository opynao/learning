#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>

std::vector<int> Reversed(const std::vector<int>&);

void testReversed()
{
	std::vector<int> vTestData {1,5,3,4,2};
	std::vector<int> controlData {2,4,3,5,1};
	assert(Reversed(vTestData) == controlData);
}

std::vector<int> Reversed(const std::vector<int>& vInts)
{
	std::vector<int> vInts_Reversed_Copy;
	vInts_Reversed_Copy.reserve(vInts.size());
	std::copy(vInts.rbegin(),vInts.rend(),std::back_inserter(vInts_Reversed_Copy));
	return vInts_Reversed_Copy;
}

int main()
{
	testReversed();
}
