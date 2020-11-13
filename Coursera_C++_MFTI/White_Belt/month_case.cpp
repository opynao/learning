#include <memory>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <utility>
#include <iostream>
#include <algorithm>
#include <functional>

enum class Months
{
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};


const std::map<Months,size_t> monthDays
{
	{Months::January,31},
	{Months::February,28},
	{Months::March,31},
	{Months::April,30},
	{Months::May,31},
	{Months::June,30},
	{Months::July,31},
	{Months::August,31},
	{Months::September,30},
	{Months::October,31},
	{Months::November,30},
	{Months::December,31}
};
	

using CaseName_t = std::string;
using Month_t = std::pair<Months,std::vector<std::vector<CaseName_t>>>;
using DayNumber_t = size_t;
using DaysCases_t = std::map<DayNumber_t,std::vector<CaseName_t>>;

size_t GetDayInMonth(const Months month)
{
	return monthDays.at(month);
}

std::unique_ptr<Month_t> CreateMonth(const Months month)
{
	return std::make_unique<Month_t>(month,GetDayInMonth(month));
}

Months GetNextMonth(const Months month)
{
	auto it {std::next(monthDays.find(month))};
	if(monthDays.cend() == it)
	{
		it = monthDays.cbegin();
	}
	return it->first;
}
	


//-------------------------------------------------------------------------



class ToDoList
{
public:
	explicit ToDoList(const std::shared_ptr<Month_t>&);
	void Add(const CaseName_t&,const DayNumber_t);
	void Dump(DaysCases_t&) const;
	void Next();
private:
	std::shared_ptr<Month_t> m_spMonth {nullptr};
	Month_t::second_type& m_rToDoList;
};

ToDoList::ToDoList(const std::shared_ptr<Month_t>& spMonth)
	: m_spMonth {spMonth}
	, m_rToDoList {spMonth->second}
{
}

void ToDoList::Add(const CaseName_t& caseName,const DayNumber_t dayNumber)
{
	m_rToDoList.at(dayNumber-1).push_back(caseName);
}

void ToDoList::Dump(DaysCases_t& dayCases) const
{
	for(size_t i = 0; i!= m_rToDoList.size(); ++i)
	{
		const auto& vCases = m_rToDoList.at(i);
		if(!vCases.empty())
		{
			dayCases.emplace(i+1,vCases);
		}
	}
}

void ToDoList::Next()
{
	m_spMonth->first = GetNextMonth(m_spMonth->first);
	const DayNumber_t newMonthDayNumbers {monthDays.at(m_spMonth->first)};
	auto& rMonth {m_spMonth->second};
	if(newMonthDayNumbers < rMonth.size())
	{
		auto itBegin {rMonth.begin()};
		std::advance(itBegin,newMonthDayNumbers);
		std::for_each(itBegin,rMonth.end(),[&rMonth,&newMonthDayNumbers](const std::vector<CaseName_t>& vCaseNames)
		{
			std::copy(vCaseNames.cbegin(),vCaseNames.cend(),std::back_inserter(rMonth.at(newMonthDayNumbers-1)));
		}
		);
	}
	rMonth.resize(newMonthDayNumbers);
}



//---------------------------------------------------------------------------




void testCreateMonth()
{
	const auto spMonth = CreateMonth(Months::March);
	assert(nullptr != spMonth);
	assert(31 == spMonth->second.size());
}

void testGetDayInMonth()
{
	assert(31 == GetDayInMonth(Months::March));
}

void testToDoList_Add_ValidDayInMonth_DayContainsOneCaseWithSameName()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::March);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	upToDoList->Add("Walk",2);
	const auto& vDay = spMonth->second.at(1); 
	assert(1 == vDay.size());
	assert("Walk" == vDay.at(0));
}

void testToDoList_Add_ValidDayInMonthSomeCases_DayContainsSomeCases()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::March);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);

	upToDoList->Add("Walk",2);
	upToDoList->Add("Salary",2);
	upToDoList->Add("Walk",2);

	const auto& vDay = spMonth->second.at(1); 
	assert(3 == vDay.size());
	const std::vector<CaseName_t> vResult {"Walk","Salary","Walk"};
	assert(vResult == vDay);
}

void testToDoList_ConstructWithMonth()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::July);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	assert(nullptr != upToDoList);
	assert(1 < spMonth.use_count());
}

void testToDoList_Dump_EmptyToDoList_Empty()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::December);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	DaysCases_t mapDayCases;
	upToDoList->Dump(mapDayCases);
	assert(mapDayCases.empty());
}

void testToDoList_Dump_OneCaseInOneDay_ResultContainOneRecordWithOneCaseName()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::June);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	upToDoList->Add("Walk",2);
	DaysCases_t mapDayCases;
	upToDoList->Dump(mapDayCases);
	assert(1 == mapDayCases.size());
	const auto& vCases = mapDayCases.at(2);
	assert(1 == vCases.size());
	assert("Walk" == vCases.at(0));
}

void testToDoList_Dump_SomeCasesInOneDay_ResultContainsSomeRecordsInOneDay()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::May);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	upToDoList->Add("Walk",1);
	upToDoList->Add("Salary",1);
	upToDoList->Add("Party",1);
	DaysCases_t mapDayCases;
	upToDoList->Dump(mapDayCases);
	assert(1 == mapDayCases.size());
	const auto& vCases = mapDayCases.at(1);
	assert(3 == vCases.size());
	std::vector<CaseName_t> vResult {"Walk","Salary","Party"};
	assert(vResult == vCases);
}

void testToDoList_Next_GoToTheNextMonth_InMonthsOrder()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::August);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	upToDoList->Next();
	assert(Months::September == spMonth->first);	
}

void testToDoList_Next_AfterDecember_MonthIsJanuary()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::December);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	upToDoList->Next();
	assert(Months::January == spMonth->first);
};


void test_GetNextMonth()
{
	assert(Months::January == GetNextMonth(Months::December));
}

void testToDoList_Next_ChangeMonthSize()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::January);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	upToDoList->Next();
	assert(28 == spMonth->second.size());
};

void testToDoList_Next_NextMonthSmallerThanPrevious_MoveAllCasesFromExtraDaysToLastDayInNewMonth()
{
	const std::shared_ptr<Month_t> spMonth = CreateMonth(Months::January);
	const auto upToDoList = std::make_unique<ToDoList>(spMonth);
	upToDoList->Add("Walk",31);
	upToDoList->Add("Salary",31);
	upToDoList->Add("Party",31);
	upToDoList->Next();
	const auto& vCases = spMonth->second.at(27);
	std::vector<CaseName_t> vResult {"Walk","Salary","Party"};
	assert(vResult == vCases);
}

void HandleAddCommand(ToDoList& todolist)
{
	DayNumber_t day {};
       	CaseName_t caseName {};
       	std::cin >> day >> caseName;
	todolist.Add(caseName,day);
}

void HandleNextCommand(ToDoList& todolist)
{
	todolist.Next();
}

void HandleDumpCommand(ToDoList& todolist)
{
	DayNumber_t day {};
	std::cin >> day;
	DaysCases_t dayCases {};
	todolist.Dump(dayCases);
	if(dayCases.find(day) != dayCases.cend())
	{
		const auto& rDayCases = dayCases.at(day);
		std::cout << rDayCases.size();
		for(const auto& caseName : rDayCases)
		{
			std::cout << " " << caseName;
		}
		std::cout << std::endl;
	}
	else
		std::cout << 0 << std::endl;
}


int main()
{
	testGetDayInMonth();
	testCreateMonth();
	testToDoList_Add_ValidDayInMonth_DayContainsOneCaseWithSameName();
	testToDoList_ConstructWithMonth();
	testToDoList_Dump_EmptyToDoList_Empty();
	testToDoList_Dump_OneCaseInOneDay_ResultContainOneRecordWithOneCaseName();
	testToDoList_Add_ValidDayInMonthSomeCases_DayContainsSomeCases();
	testToDoList_Dump_SomeCasesInOneDay_ResultContainsSomeRecordsInOneDay();
	testToDoList_Next_GoToTheNextMonth_InMonthsOrder();
	testToDoList_Next_AfterDecember_MonthIsJanuary();
	test_GetNextMonth();
	testToDoList_Next_ChangeMonthSize();
	testToDoList_Next_NextMonthSmallerThanPrevious_MoveAllCasesFromExtraDaysToLastDayInNewMonth();
	

		
	ToDoList todolist(CreateMonth(Months::January));
	using CommandHandler_t = void(*)(ToDoList&);
	std::map<std::string,CommandHandler_t> cmdHandlers 
	{
		{"ADD",&HandleAddCommand},
		{"DUMP",&HandleDumpCommand},
		{"NEXT",&HandleNextCommand}
	};
	size_t numberOfCalls {};
	std::cin >> numberOfCalls;
	while(numberOfCalls--)
	{
		std::string command {};
		std::cin >> command;
		auto it {cmdHandlers.find(command)};
		if(it != cmdHandlers.cend())
		{
			std::bind(*it->second,todolist)();
		}
	}
	return 0;
}
