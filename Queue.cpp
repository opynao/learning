#include <memory>
#include <cassert>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>

enum class StatesOfMind
{
	Quiet,
	Worry
};

class Person
{
public:
	explicit Person(const StatesOfMind);
	StatesOfMind GetStateOfMind() const;
	void SetStateOfMind(const StatesOfMind);
private:
	StatesOfMind m_StateOfMind;	
};

Person::Person(const StatesOfMind stateOfMind)
	: m_StateOfMind {stateOfMind}
{}

StatesOfMind Person::GetStateOfMind() const
{
	return m_StateOfMind;
}	


void Person::SetStateOfMind(const StatesOfMind stateOfMind)
{
	m_StateOfMind = stateOfMind;
}
// -----------------------------------------------------------------------------
using PersonCount_t = int;
using Position_t = size_t;

class IQueue
{
public:
	virtual	PersonCount_t WorryCount() const = 0;	
	virtual void Come(const PersonCount_t) = 0;
	virtual void Worry(const Position_t) = 0;
	virtual void Quiet(const Position_t) = 0;
};

class Queue : public IQueue
{
public:
	virtual	PersonCount_t WorryCount() const override;	
	virtual void Come(const PersonCount_t) override;
	virtual void Worry(const Position_t) override;
	virtual void Quiet(const Position_t) override;
	virtual ~Queue();
private:
	void AddPersons(const PersonCount_t);
	void ErasePersons(const PersonCount_t);
	std::vector<Person> m_vPersons {};
};

void Queue::Quiet(const Position_t position)
{
	m_vPersons.at(position).SetStateOfMind(StatesOfMind::Quiet);	
}


void Queue::Worry(const Position_t position)
{
	m_vPersons.at(position).SetStateOfMind(StatesOfMind::Worry);	
}

PersonCount_t Queue::WorryCount() const
{
	return std::count_if(std::cbegin(m_vPersons),std::cend(m_vPersons),[](decltype(m_vPersons)::const_reference item) -> bool {return StatesOfMind::Worry == item.GetStateOfMind();});
}

void Queue::Come(const PersonCount_t personCount)
{
	if(personCount >= 0)
		AddPersons(personCount);
	else
		ErasePersons(personCount);
}

void Queue::AddPersons(const PersonCount_t personCount)
{
	m_vPersons.insert(std::cend(m_vPersons),personCount,Person{StatesOfMind::Quiet});
}

void Queue::ErasePersons(const PersonCount_t personCount)
{
	auto itFirst = std::end(m_vPersons);
	auto itLast = std::end(m_vPersons);
	std::advance(itFirst,personCount);
	m_vPersons.erase(itFirst,itLast);
}

Queue::~Queue()
{}

class QueueMoc : public IQueue
{
public:
	virtual	PersonCount_t WorryCount() const override {bIsWorryCount = true; return 1;}
	virtual void Come(const PersonCount_t pc) override {bIsCome = true; personCount = pc;}
	virtual void Worry(const Position_t pos) override {bIsWorry = true; position = pos;}
	virtual void Quiet(const Position_t pos) override {bIsQuiet = true; position = pos;}
	virtual ~QueueMoc() {}
	
	bool IsWorryCount() const {return bIsWorryCount;}
	std::pair<bool,PersonCount_t> IsCome() const {return { bIsCome, personCount}; }
	std::pair<bool,Position_t> IsWorry() const {return { bIsWorry, position}; }
	std::pair<bool,Position_t> IsQuiet() const {return { bIsQuiet, position}; }
private:
	mutable	bool bIsWorryCount {false};
	bool bIsCome {false};
	bool bIsWorry {false};
	bool bIsQuiet {false};
	PersonCount_t personCount {};
	Position_t position {};
};

//-----------------------------------------------------------------------------


class QueueIOController
{
public:
	QueueIOController(const std::shared_ptr<IQueue>&,std::istream&,std::ostream&);
	void GetCommand();
private:
	void GetComeCommand();
	void GetWorryCommand();
	void GetWorryCountCommand();
	void GetQuietCommand();

	const std::shared_ptr<IQueue> m_spQueue {};
	std::istream& m_is;
	std::ostream& m_os;

	using CommandName_t = std::string;
	typedef void (QueueIOController::*CommandExec_t)();
	std::map<CommandName_t,CommandExec_t> m_Commands {
		{"COME",&QueueIOController::GetComeCommand },
		{"WORRY",&QueueIOController::GetWorryCommand },
		{"WORRY_COUNT",&QueueIOController::GetWorryCountCommand },
		{"QUIET",&QueueIOController::GetQuietCommand }
	};
};

QueueIOController::QueueIOController(const std::shared_ptr<IQueue>& spQueue,std::istream& is,std::ostream& os)
	: m_spQueue {spQueue}
	, m_is {is}
	, m_os {os}
{}

void QueueIOController::GetComeCommand()
{
	PersonCount_t personCount {};
	m_is >> personCount;
	m_spQueue->Come(personCount);
}
void QueueIOController::GetWorryCommand()
{
	Position_t position;
	m_is >> position;
	m_spQueue->Worry(position);
}

void QueueIOController::GetWorryCountCommand()
{
	m_os << m_spQueue->WorryCount() << std::endl;
}

void QueueIOController::GetQuietCommand()
{
	Position_t position;
	m_is >> position;
	m_spQueue->Quiet(position);
}

void QueueIOController::GetCommand()
{
	std::string commandName {};
	m_is >> commandName;
	const auto it = m_Commands.find(commandName);
        if(it != m_Commands.cend())
		std::bind(it->second, this)();
	       
}

//-----------------------------------------------------------------------------
void testPersonConstructWithStatesOfMind_Quiet()
{
	const auto upPerson = std::make_unique<Person>(StatesOfMind::Quiet);
	assert(nullptr != upPerson);
	assert(StatesOfMind::Quiet == upPerson->GetStateOfMind());
}

void testPersonConstructWithStatesOfMind_Worry()
{
	const auto upPerson = std::make_unique<Person>(StatesOfMind::Worry);
	assert(nullptr != upPerson);
	assert(StatesOfMind::Worry == upPerson->GetStateOfMind());
}

void testPerson_GetStateOfMind_AfterConstruct_EqualToConstructParam()
{
	const auto upPerson = std::make_unique<Person>(StatesOfMind::Quiet);
	assert(StatesOfMind::Quiet == upPerson->GetStateOfMind());
}

void testPerson_SetStateOfMind_Quiet_GetStateOfMindReturnQuiet()
{
	const auto upPerson = std::make_unique<Person>(StatesOfMind::Quiet);
	upPerson->SetStateOfMind(StatesOfMind::Quiet);
	assert(StatesOfMind::Quiet == upPerson->GetStateOfMind());
}

void testPerson_SetStateOfMind_Worry_GetStateOfMindReturnWorry()
{
	const auto upPerson = std::make_unique<Person>(StatesOfMind::Worry);
	upPerson->SetStateOfMind(StatesOfMind::Worry);
	assert(StatesOfMind::Worry == upPerson->GetStateOfMind());
}

void testQueueDefaultConstruct()
{
	const auto upQueue = std::make_unique<Queue>();
	assert(nullptr != upQueue);
}

void testQueue_WorryCount_EmptyQueue_ReturnZero()
{
	const auto upQueue = std::make_unique<Queue>();
	assert(0 == upQueue->WorryCount());
}

void testQueue_Come_InEmptyQueue_WorryCountReturnZero()
{
	const auto upQueue = std::make_unique<Queue>();
	upQueue->Come(3);
	assert(0 == upQueue->WorryCount());
}

void testQueue_Worry_WorryCountReturnMoreOne()
{
	const auto upQueue = std::make_unique<Queue>();
	upQueue->Come(3);
	upQueue->Worry(1);
	assert(1 == upQueue->WorryCount());
}

void testQueue_Come_QueueContainsWorriedPersons_WorryCountDontChangeAfterComeNewPersons()
{
	const auto upQueue = std::make_unique<Queue>();
	upQueue->Come(3);
	upQueue->Worry(1);
        const PersonCount_t worryCountBeforeMorePersonsCome = upQueue->WorryCount();
	upQueue->Come(2);
	const PersonCount_t worryCountAfterNewPersonsCome = upQueue->WorryCount();
	assert(worryCountBeforeMorePersonsCome == worryCountAfterNewPersonsCome);
}

void testQueue_ComeWithNegativeArg_QueueWithSixWorriedPersons_LeaveThree_ResultThreeWorriedPersonsInQueue()
{
	const auto upQueue = std::make_unique<Queue>();
	upQueue->Come(6);
	for(size_t i = 0; i!=6; ++i)
	{
		upQueue->Worry(i);
	}
	upQueue->Come(-3);
	assert(3 == upQueue->WorryCount());
}

void testQueueIOController_Construct()
{
	const auto spQueue = std::make_shared<QueueMoc>();
	const auto upQueueIOController = std::make_unique<QueueIOController>(spQueue,std::cin,std::cout);
	assert(nullptr != upQueueIOController);
}

void testQueueIOController_GetCommand_Come()
{
	const auto spQueueMoc = std::make_shared<QueueMoc>();
	const std::string commandString {"COME 5"};
	std::stringstream iss(commandString);
	std::stringstream oss;
	const auto upQueueIOController = std::make_unique<QueueIOController>(spQueueMoc,iss,oss);
	upQueueIOController->GetCommand();
	assert(true == spQueueMoc->IsCome().first);
	assert(5 == spQueueMoc->IsCome().second);
	assert(true == oss.str().empty());
}

void testQueueIOController_GetCommand_Worry()
{
	const auto spQueueMoc = std::make_shared<QueueMoc>();
	const std::string commandString {"WORRY 5"};
	std::stringstream iss(commandString);
	std::stringstream oss;
	const auto upQueueIOController = std::make_unique<QueueIOController>(spQueueMoc,iss,oss);
	upQueueIOController->GetCommand();
	assert(true == spQueueMoc->IsWorry().first);
	assert(5 == spQueueMoc->IsWorry().second);
	assert(true == oss.str().empty());
}

void testQueueIOController_GetCommand_WorryCount()
{
	const auto spQueueMoc = std::make_shared<QueueMoc>();
	const std::string commandString {"WORRY_COUNT"};
	std::stringstream iss(commandString);
	std::stringstream oss;
	const auto upQueueIOController = std::make_unique<QueueIOController>(spQueueMoc,iss,oss);
	upQueueIOController->GetCommand();
	assert(true == spQueueMoc->IsWorryCount());
	assert("1\n" == oss.str());
}

void testQueueIOController_GetCommand_Quiet()
{
	const auto spQueueMoc = std::make_shared<QueueMoc>();
	const std::string commandString {"QUIET 5"};
	std::stringstream iss(commandString);
	std::stringstream oss;
	const auto upQueueIOController = std::make_unique<QueueIOController>(spQueueMoc,iss,oss);
	upQueueIOController->GetCommand();
	assert(true == spQueueMoc->IsQuiet().first);
	assert(5 == spQueueMoc->IsWorry().second);
	assert(true == oss.str().empty());
}

void testQueue_Quiet_QueueContainsWorriedPersons_WorryCountChangeAfterQuietOneWorriedPerson()
{
	const auto upQueue = std::make_unique<Queue>();
	upQueue->Come(3);
	upQueue->Worry(1);
        const PersonCount_t worryCountBeforeMorePersonsCome = upQueue->WorryCount();
	upQueue->Quiet(1);
	const PersonCount_t worryCountAfterQuietOnePerson = upQueue->WorryCount();
	assert(1 == worryCountBeforeMorePersonsCome - worryCountAfterQuietOnePerson);
}

int main()
{
	testPersonConstructWithStatesOfMind_Worry();
	testPersonConstructWithStatesOfMind_Quiet();
	testPerson_GetStateOfMind_AfterConstruct_EqualToConstructParam();
	testPerson_SetStateOfMind_Quiet_GetStateOfMindReturnQuiet();
	testPerson_SetStateOfMind_Worry_GetStateOfMindReturnWorry();
	testQueue_Come_InEmptyQueue_WorryCountReturnZero();
	testQueue_WorryCount_EmptyQueue_ReturnZero();
	testQueueDefaultConstruct();
	testQueue_Worry_WorryCountReturnMoreOne();
	testQueue_Come_QueueContainsWorriedPersons_WorryCountDontChangeAfterComeNewPersons();
	testQueue_ComeWithNegativeArg_QueueWithSixWorriedPersons_LeaveThree_ResultThreeWorriedPersonsInQueue();
	testQueueIOController_Construct();
	testQueueIOController_GetCommand_Come();
	testQueueIOController_GetCommand_Worry();
	testQueueIOController_GetCommand_WorryCount();
	testQueueIOController_GetCommand_Quiet();
	testQueue_Quiet_QueueContainsWorriedPersons_WorryCountChangeAfterQuietOneWorriedPerson();
	size_t numberOfCommands {};
	std::cin >> numberOfCommands;
	const auto spQueue = std::make_shared<Queue>();
	QueueIOController qc(spQueue,std::cin,std::cout);
	while(numberOfCommands--)
	{
		qc.GetCommand();
	}
	return 0;
}
