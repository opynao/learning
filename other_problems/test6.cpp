#include <iostream>
#include <vector>

int main()
{
	std::vector<int> num(1,5);
	num.push_back(1);
	num.push_back(4);
//	num.push_back(3);
	for(int s:num)
	{
		std::cout << s;
	}
	num.clear();
	std::cout << num.size();
	return 0;
}
