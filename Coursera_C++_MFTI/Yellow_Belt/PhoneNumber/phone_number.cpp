#include <string>
#include <stdexcept>
#include <sstream>
#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const std::string &international_number)
{
	char ch;
	const char delimiter {'-'};
	std::istringstream ss;
	ss.str(international_number);
	ss.get(ch);
	if(ch != '+')
		throw std::invalid_argument("");
	std::getline( ss, country_code_, delimiter );
	std::getline( ss, city_code_, delimiter );
	std::getline( ss, local_number_ );
}

std::string PhoneNumber::GetCountryCode() const
{
	return country_code_;
}

std::string PhoneNumber::GetCityCode() const
{
	return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const
{
	return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const
{
	std::string result = "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
	return result;
}

