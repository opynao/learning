#include <iostream>

unsigned gcd(unsigned a, unsigned b)
{
	while (a>0 && b>0)
	{
		if(a>b)
			a = a%b;
		else
			b = b%a;
	}
	return a+b;
}

int main()
{
	int a {};
	int b {};
	std::cin >> a >> b;
	std::cout << gcd(a,b);
	return 0;
}



