#include <iterator>
#include <vector>
#include <numeric>
#include <iostream>
#include <cassert>
#include <algorithm>

using Temp_t = std::vector<int>;
using Days_t = std::vector<int>;
using AverageTemp_t = int;
using Temperature_t = int;
Temp_t GetVector(const size_t);
AverageTemp_t CalculateAverageTemperature(const Temp_t&);
Days_t GetDaysNumbers(const Temp_t&,const AverageTemp_t);
void PrintVector(const Days_t&);

void testTemperatureCalendar()
{
	TemperatureCalendar tc;
}


class Temperature

void testCalculateAverageTemperature()
{
	assert(CalculateAverageTemperature({7,6,3,0,9}) == 5);
}

void testGetDaysNumbers()
{
	Temp_t vTemp = {7,6,3,0,9};
	Temp_t vDays = {0,1,4};
	assert(GetDaysNumbers(vTemp,CalculateAverageTemperature(vTemp)) == vDays);
}	

Temp_t GetVector(const size_t numberOfDays)
{
	Temp_t vTemp {};
	vTemp.reserve(numberOfDays);
	Temperature_t temperature {};
	while(numberOfDays-- != 0)
	{
		std::cin >> temperature;
		vTemp.push_back(temperature);
	}
	return vTemp;
}

AverageTemp_t CalculateAverageTemperature(const Temp_t& vTemp)
{
	return std::accumulate(std::begin(vTemp),std::end(vTemp),0)/vTemp.size();
}

Days_t GetDaysNumbers(const Temp_t& vTemp,const AverageTemp_t averageTemp)
{
	Days_t vDays {};
	for (size_t i = 0; i != vTemp.size(); ++i)
	{
		if (vTemp[i] > averageTemp)
			vDays.push_back(i);
	}
	/*
	for (auto it = vTemp.cbegin(); it != vTemp.cend(); std::next(it))
	{
		vDays.emplace_back(std::distance(vTemp.cbegin(),it));
		it = std::find_if(std::next(it),std::end(vTemp),
		[&averageTemp]( Temp_t::const_reference temp ) 
		{
			return temp > averageTemp;
		});
	}
	*/
	return vDays;
}

void PrintVector(const Days_t& vDays)
{
	for(int s:vDays)
	{
		std::cout << s << " ";
	}
}

int main()
{
	size_t numberOfDays {};
	std::cin >> numberOfDays;
	Temp_t vTemp = GetVector(numberOfDays);
	Days_t vDays = GetDaysNumbers(vTemp,CalculateAverageTemperature(vTemp));
	std::cout << vDays.size() << std::endl;
	PrintVector(vDays);
/*
	testCalculateAverageTemperature();
	testGetDaysNumbers();
*/
	return 0;	
}
