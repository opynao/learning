#pragma once
#include <string>
#include <ostream>

class Date 
{
public:
	Date() = default;
	explicit Date(const std::string&);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	static bool CheckFormat(const std::string&);
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
