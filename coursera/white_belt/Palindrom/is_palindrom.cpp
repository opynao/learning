#include "IsPalindrom.h"
#include <cassert>
#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>

void TestIsPalindrom()
{
	using vTestData_t = std::vector<std::pair<std::string,bool>>;
	vTestData_t vTestData {{"madam",true},{"gentelmen",false},{"X",true},{"",true}};
	std::for_each(vTestData.cbegin(),vTestData.cend(),[](vTestData_t::const_reference vTestData)
			{
				assert(IsPalindrom(vTestData.first) == vTestData.second);
			}
		     );
}

bool IsPalindrom(const std::string& str)
{
	std::string str_copy{};
        copy(str.rbegin(),str.rend(),std::back_inserter(str_copy));
	return str_copy == str;
}
