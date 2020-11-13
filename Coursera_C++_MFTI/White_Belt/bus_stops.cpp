#include <cassert>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#define LOGF std::cerr << __FUNCTION__ << std::endl;


using busNumber_t = std::string;
using stopName_t = std::string;
using numberOfStops_t = size_t;
using vBusStops_t = std::vector<stopName_t>;
using commandName_t = std::string;
using busInfo_t = std::map<busNumber_t,vBusStops_t>;
using vBusNumber_t = std::vector<busNumber_t>;
using stopInfo_t = std::map<stopName_t,vBusNumber_t>;

void NewBusCommand(busInfo_t&,stopInfo_t&);
void BusesForStopCommand(busInfo_t&,stopInfo_t&);
void StopsForBusCommand(busInfo_t&,stopInfo_t&);
void AllBusesCommand(busInfo_t&,stopInfo_t&);

std::map<commandName_t,void(*)(busInfo_t&,stopInfo_t&)> mInputCases
{
	{"NEW_BUS",&NewBusCommand},
	{"BUSES_FOR_STOP",&BusesForStopCommand},
	{"STOPS_FOR_BUS",&StopsForBusCommand},
	{"ALL_BUSES",&AllBusesCommand}
};

//--------------NEW-BUS-COMMAND-------------------------------

void NewBusCommand(busInfo_t& mBusInfo,stopInfo_t& mStopInfo)
{
	LOGF;
	busNumber_t busNumber {};
	stopName_t stopName {};
	numberOfStops_t numberOfStops {};
	vBusStops_t vBusStops {};
	std::cin >> busNumber >> numberOfStops;
	vBusStops.reserve(numberOfStops);
	while(numberOfStops--)
	{
		std::cin >> stopName;
		vBusStops.push_back(stopName);
	}
	mBusInfo.emplace(busNumber,vBusStops);
	std::for_each(vBusStops.cbegin(),vBusStops.cend(),[&mStopInfo,&busNumber](decltype(vBusStops)::const_reference str)
			{
				mStopInfo.emplace(str,vBusNumber_t {busNumber});
			}
		     );
}

//----------------BUSES-FOR-STOP-COMMAND----------------------

void BusesForStopCommand(busInfo_t& mBusInfo,stopInfo_t& mStopInfo)
{
	LOGF;
	stopName_t stopName {};
	std::cin >> stopName;
	if(mStopInfo.count(stopName) == 0)
		std::cout << "No stop";
	else
	{
		const auto itStop = mStopInfo.find(stopName);
		for(const auto& bus : itStop->second)
		{
			std::cout << bus << " ";
		}
		std::cout << std::endl;
	}
}


//--------------STOPS-FOR-BUS-COMMAND------------------------

void StopsForBusCommand(busInfo_t& mBusInfo,stopInfo_t& mStopInfo)
{
	LOGF;
	busNumber_t busNumber {};
	std::cin >> busNumber;
	if(mBusInfo.count(busNumber) == 0)
	{
		std::cout << "No bus";
	}
	else
	{
		vBusStops_t vBusStops = mBusInfo.at(busNumber);
		std::for_each(std::cbegin(vBusStops),std::cend(vBusStops),[&mStopInfo,&busNumber](decltype(vBusStops)::const_reference str)
				{
					vBusNumber_t vBusNumber = mStopInfo.at(str);
					const size_t pos = vBusNumber[busNumber];
					vBusNumber.erase(pos);
					std::cout << "Stop " << str << ": ";
					if(vBusNumber.empty())
						std::cout << "No interchange";
					else
					{
						for(const auto& busNumber : vBusNumber)
						{
							std::cout << busNumber << " ";
						}
					}
					std::cout << std::endl;
				}
			     );
	}
}

//-------------ALL-BUSES-COMMAND-----------------------------

void AllBusesCommand(busInfo_t& mBusInfo,stopInfo_t& mStopInfo)
{
	LOGF;
	if(mBusInfo.empty())
		std::cout << "No buses";
	else
	{
		using mBusInfo_t = std::remove_reference<decltype(mBusInfo)>::type;
		std::for_each(std::cbegin(mBusInfo),std::cend(mBusInfo),[](mBusInfo_t::const_reference pr)
				{
					std::cout << "Bus " << pr.first << ": ";
					for(const auto& stop : pr.second)
					{
						std::cout << stop << " ";
					}
					std::cout << std::endl;
				}
			     );
	}
}


//-------------CALLING-MODULE-------------------------------


void CallingModule(busInfo_t& mBusInfo,stopInfo_t& mStopInfo)
{
	LOGF;
	std::string command {};
	std::cin >> command;
	auto itCall = mInputCases.find(command);
	if(mInputCases.cend() != itCall)
	{
		itCall->second(mBusInfo,mStopInfo);
	}
}


//--------------------TESTS----------------------------------



//-------------------MAIN-------------------------------------


int main()
{
	size_t NumberOfCalls {};
	std::cin >> NumberOfCalls;
	busInfo_t mBusInfo {};
	stopInfo_t mStopInfo {};
	while(NumberOfCalls--)
	{
		CallingModule(mBusInfo,mStopInfo);
	}
	std::cerr << mBusInfo.size() << " " << mStopInfo.size() << std::endl;
	return 0;
}
