#include <cassert>
#include <vector>
#include <iostream>
#include "tests.h"
#include "find_greater_elems.h"
#define LOGF std::cerr << __FUNCTION__ << std::endl;

using namespace std;

void testFindGreaterElemsCorrectInput()
{
	LOGF;
	std::set<int> input {1,5,7,8};
	std::vector<int> result {7,8};
	std::cerr << FindGreaterElements(input, 5).size();
	assert(result == FindGreaterElements(input, 5));
}

void testFindGreaterElems_NoBorderInSet()
{
	LOGF;
	std::set<std::string> input {"C","C++"};
	std::vector<std::string> result {};
	std::string border {"Python"};
	assert(result == FindGreaterElements(input, border));
}

void testFindGreaterElems_EmptySet()
{
	LOGF;
	std::set<std::string> input {};
	std::vector<std::string> result {};
	std::string border {"Python"};
	assert(result == FindGreaterElements(input, border));
}


void TestAll()
{
	testFindGreaterElemsCorrectInput();
	testFindGreaterElems_NoBorderInSet();
	testFindGreaterElems_EmptySet();
}


