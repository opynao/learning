#pragma once
#include <iostream>

#define LOG(message) std::cerr << message << std::endl
#define LOGN(message, number) std::cerr << message  << number << std::endl
#define LOGF std::cerr << __FUNCTION__ << " = " << __LINE__ << std::endl
#define PR(x) std::cerr << #x << " = " << x << std::endl