#include <bitset>
#include <iostream>
#include <iomanip>

int main()
{
	int n {};
	std::stringstream ss {};
	std::cin >> n;
	std::bitset<64> x(n);
	ss << x;
	std::string str = ss.str();
	size_t pos = str.find('1');
	std::cout << str.substr(pos,str.size()-pos);
	return 0;
}
