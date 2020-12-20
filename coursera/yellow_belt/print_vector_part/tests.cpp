#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include "tests.h"
#include "print_vector_part.h"

void testPrintVectorPart()
{
	std::vector<int> vInts {6,1,8,-5,4};
	std::ostringstream oss;
	PrintVectorPart(vInts, oss);
	std::string result {"8 1 6"};
	assert(oss.str() == result);
}

void testPrintVectorPart2()
{
	std::vector<int> vInts {-6,1,8,-5,4};
	std::ostringstream oss;
	PrintVectorPart(vInts, oss);
	std::string result {""};
	assert(oss.str() == result);
}

void testPrintVectorPart3()
{
	std::vector<int> vInts {6,1,8,5,4};
	std::ostringstream oss;
	PrintVectorPart(vInts, oss);
	std::string result {"4 5 8 1 6"};
	assert(oss.str() == result);
}

void testPrintVectorPart4()
{
	std::vector<int> vInts {};
	std::ostringstream oss;
	PrintVectorPart(vInts, oss);
	std::string result {""};
	assert(oss.str() == result);
}

void TestAll()
{
	testPrintVectorPart();
	testPrintVectorPart2();
	testPrintVectorPart3();
	testPrintVectorPart4();
}

