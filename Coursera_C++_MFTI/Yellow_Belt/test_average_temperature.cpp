#include <vector>
#include <iostream>


int main()
{
	std::vector<int> t = {-3,-2,1};
	int sum = 0;
	for (int x : t)
	{
		sum += x;
	}
	std::cout << t.size() << std::endl;
	int size = t.size();
	int avg = sum/size;
	std::cout << avg << std::endl;
	return 0;
}

