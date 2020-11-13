#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <chrono>

using vWords_t = std::vector<std::string>;

using vTestData_t = std::pair<std::pair<vWords_t,int>,vWords_t>;

vWords_t PalindromFilter(const vWords_t&,const int);

bool IsPalindrom(const std::string& str);

void testPalindromFilter_Input1()
{
	const vTestData_t input = {{{"abacaba","aba"},5},{"abacaba"}};
	assert(PalindromFilter(input.first.first,input.first.second) == input.second);
}


void testPalindromFilter_Input2()
{
	const vTestData_t input = {{{"abacaba","aba"},2},{"abacaba","aba"}};
	assert(PalindromFilter(input.first.first,input.first.second) == input.second);
}


void testPalindromFilter_Input3()
{
	assert(PalindromFilter({"weew","bro","code"},4}) == {"weew"});
}


void testPalindromFilter_Input4()
{
	assert(PalindromFilter({"","",""},4) == {});
}

auto start = std::chrono::steady_clock::now();

vWords_t PalindromFilter(const vWords_t& vWords_from,const int minLength)
{
	vWords_t vWords_to;
	std::copy_if(vWords_from.begin(),vWords_from.end(),std::back_inserter(vWords_to),[&minLength]( vWords_t::const_reference val ) -> bool { return IsPalindrom(val) && val.size() >= minLength; });
	return vWords_to;
}

auto end = std::chrono::steady_clock::now();

auto start1 = std::chrono::steady_clock::now();

bool IsPalindrom(const std::string& str)
{
	std::string str_copy{};
        copy(str.rbegin(),str.rend(),std::back_inserter(str_copy));
	return str_copy == str;
}

auto end1 = std::chrono::steady_clock::now();

int main()
{
	std::chrono::duration<double> diff = end - start;
	std::cout << diff.count() << std::endl;
	std::chrono::duration<double> diff1 = end1 - start1;
	std::cout << diff1.count();
	return 0;
}
