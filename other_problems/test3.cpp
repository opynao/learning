#include <iostream>

auto compose(int a, int b)
{
	auto y = a+b;
	return y;
}


int main()
{
	int a = 3;
	int b = 2;
	std::cout << compose(a,b);
	return 0;
}
