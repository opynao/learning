#include <iostream>

int division(int a, int b)
{
	return int(a/b);
}

int main()
{
	int a{};
	int b{};
	std::cin >> a >> b;
	if( b!= 0 )
	{
		std::cout << division (a,b);
	}
	else
		std::cout << "Impossible";
	return 0;
}
