#include <map>
#include <iostream>


std::map<int,int> m {{1,2},{1,3},{4,5}};

int main()
{
//	m[2] += 1;
	for(const auto& item : m)
	{
		std::cout << item.second;
	}
	return 0;
}

