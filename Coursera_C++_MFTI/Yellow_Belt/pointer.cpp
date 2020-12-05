#include <iostream>

void foo(int a)
{
	a = a * a;
	std::cout << "Значение аргумента в функции " << a << std::endl;
}

int main()
{
	std::cout << "Передача аргумента в функцию по значению" << std::endl;
	int a = 2;
	foo(a);
	std::cout << "После вызова функции " << a << std::endl;
	return 0;
}

