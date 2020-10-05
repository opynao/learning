#include <cstddef>
#include <vector>
#include <cassert>
#include <cstdint>
#include <iterator>

std::vector<std::vector<uint32_t>>::value_type::value_type 
	Find( const std::vector<std::vector<uint32_t>>&,
	      const std::vector<std::vector<uint32_t>>::size_type,
	      const std::vector<std::vector<uint32_t>>::value_type::size_type);

std::vector<std::vector<uint32_t>>::value_type::value_type 
	Find( const std::vector<std::vector<uint32_t>>& vArray,
	      const std::vector<std::vector<uint32_t>>::size_type IndexA,
	      const std::vector<std::vector<uint32_t>>::value_type::size_type IndexK)
{
	return vArray[IndexA][IndexK];
}

std::vector<std::vector<uint32_t>>::const_iterator 
	FindCopy( const std::vector<std::vector<uint32_t>>& vArray,
	      const std::vector<std::vector<uint32_t>>::size_type IndexA,
	      const std::vector<std::vector<uint32_t>>::value_type::size_type IndexK)
{
	return vArray.begin();
}

void TestFindWithCorrectValueOfIndices()
{
	std::vector<std::vector<uint32_t>> vArray 
	{
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	assert(Find(vArray,0,3) == 4);
}

void TestFindWithIncorrectValueOfIndices()
{
	std::vector<std::vector<uint32_t>> vArray
	{
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	assert(FindCopy(vArray,30,30) == vArray.end());
}

void RunTests()
{
	TestFindWithCorrectValueOfIndices();
	TestFindWithIncorrectValueOfIndices();
}

int main()
{
	RunTests();
	return 0;
}
