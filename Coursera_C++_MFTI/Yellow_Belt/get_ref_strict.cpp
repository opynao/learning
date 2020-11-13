#include <map>
#include <cassert>
#include <exception>
#include <iostream>

template <typename T1, typename T2>
T2& GetRefStrict(std::map<T1,T2>& m, T1 key)
{
	if (m.count(key) == 0)
		throw (std::runtime_error(""));
	auto itFind = m.find(key);
	return itFind->second;
}


void testGerRefStrict()
{
	std::map<int,int> m 
	{
		{1,2},
		{2,3}
	};
	bool isException = false;
	try
	{
		GetRefStrict(m,3);
	}
	catch(std::runtime_error&)
	{
		isException = true;
	}
	assert(isException);
}

void RunAllTests()
{
	testGerRefStrict();

}

using namespace std;

int main()
{
	RunAllTests();
	return 0;
}
