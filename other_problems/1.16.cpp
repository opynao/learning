#include <iostream>
#include <string>

int main()
{
	std::string strMax {};
	std::cout << "Enter strings: " << std::endl;
	while ( true )
	{
		std::string str {};
		std::getline( std::cin, str );
		if ( !str.empty() )
		{
			if ( str.length() > strMax.length() )
			{
				strMax = str;
			}
		}
		else
			break;
	}
	std::cout << strMax << std::endl;
	return 0;
}
