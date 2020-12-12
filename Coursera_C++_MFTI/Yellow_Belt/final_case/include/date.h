#pragma once
#include <string>
#include <ostream>
#include <vector>

class Date 
{
public:
	Date() = default;
	explicit Date(const std::string&);
	Date(const int, const int, const int);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year {};
	int month {};
	int day {};
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
std::ostream& operator<<(std::ostream& os, const Date& date);
