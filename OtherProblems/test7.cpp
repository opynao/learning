#include <iostream>
#include <string>

int main()
{
	std::string s;
	s += "Hello";
	{
		s += "world";
	}
	std::cout <<s;
	return 0;
}
