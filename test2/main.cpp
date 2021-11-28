#include <tuple>
#include <string>
#include <iostream>

int main()
{
    auto t = std::make_tuple<int, std::string>(1, "str");
    std::get<int>(t) = 3;
    std::cout << std::get<int>(t) << std::endl;
}