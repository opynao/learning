#include <iostream>

int main()
{
	int a {};
	int b {};
	std::cin >> a >> b;
	if (a%2 == 0)
	{
		for(int i = a; i<= b; i += 2)
		{
			std::cout << i << " ";
		}
	}
	else
	{
		a = a + 1;
		for(int i = a; i <=b; i += 2)
		{
			std::cout << i << " "; 
		}
	}
	return 0;
}
