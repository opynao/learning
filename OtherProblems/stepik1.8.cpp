#include <iostream>
#include <vector>
#include <algorithm>

int Log2(const int number)
{
    if(number == 1)
    {
	return 0;
    }
    return Log2(number/2) + 1;
}

int main()
{
    int NumberOfInputs {};
    std::cin >> NumberOfInputs;
    int Input {};
    std::vector<int> vInputs {};
    while(NumberOfInputs--)
    {
        std::cin >> Input;         
        vInputs.push_back(Input);
    }
    std::for_each(vInputs.cbegin(),vInputs.cend(),[](int n){std::cout<<Log2(n)<<std::endl;});
    return 0;
}
