#include <sstream>
#include <cassert>
#include <string>
#include <memory>
#include <iostream>
#define LOGF std::cerr<<__FUNCTION__<<std::endl

using event_t = std::string;
using command_t = std::string;

//------------------CLASS-DATE----------------


class Date {
public:
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
};

bool operator<(const Date& lhs, const Date& rhs);


//---------------CLASS-DATABASE-------------------


class Database {
public:
	void AddEvent(const Date&, const event_t&);
	bool DeleteEvent(const Date&, const event_t&);
	int  DeleteDate(const Date&);
	event_t Find(const Date&) const;
	void Print() const;
};

void Database::AddEvent(const Date& date, const event_t& event)
{
}

bool Database::DeleteEvent(const Date& date, const event_t& event)
{
	return 1;
}

int Database::DeleteDate(const Date& date)
{
	return 1;
}

event_t Database::Find(const Date& date) const
{
	return "event1";
}

void Database::Print() const
{
}


//-----------------------------------------------

//----------------CLASS-COMMANDPARSER-------------

class IODatabaseAdapter
{
public:
	IODatabaseAdapter(std::istream&,std::ostream&,Database&);
	void Run() const;
private:
	std::ostream& m_os;
};

IODatabaseAdapter::IODatabaseAdapter(std::istream& is,std::ostream& os,Database& db)
	: m_os {os}
{
	
}

void IODatabaseAdapter::Run() const
{
	
	const auto command = commandParser.GetCommand();
	command.Execute(db,m_os);
}

class AddCommand
{
public:
	void Execute(Database&,std::ostream&);
};

class ICommandParser
{
public:
	AddCommand GetCommand() = 0;
};

void AddCommand::Execute(Database& db,std::ostream& os)
{
	os.str("1");
}

//-------------------TESTS-----------------------------

/*
void testIODatabaseAdapter_Run_InputCorrectCommands_OutputResultOfCommandExecution()
{
	LOGF;
	Database db;
	std::istringstream is;
	std::ostringstream os;
	is.str("Add 0-1-2 event1\nAdd 1-2-3 event2\nFind 0-1-2\nDel 0-1-2\nPrint\nDel 1-2-3 event2\nDel 1-2-3 event2\n");
	IODatabaseAdapter ioDatabaseAdapter(is, os, db);
	ioDatabaseAdapter.Run();
	const std::string strResult {"event1\nDeleted 1 events\n0001-02-03 event2\nDeleted successfully\nEvent not found\n"};
	assert(strResult == os.str());
}

void testIODatabaseAdapter_Run_InputAddPrintCommands_OutputResultPrintOfOneEvent()
{
	LOGF;
	Database db;
	std::istringstream is;
	std::ostringstream os;
	is.str("Add 0-1-2 event1\nPrint\n");
	IODatabaseAdapter ioDatabaseAdapter(is, os, db);
	ioDatabaseAdapter.Run();
	const std::string strResult {"0001-01-02 event1\n"};
	assert(strResult == os.str());
}
*/


void testAddCommandExecute_CorrectCommand_OstreamIsEmpty()
{
	LOGF;	
	AddCommand cmd;
	Database db;
	std::ostringstream os;
	cmd.Execute(db,os);
	assert(os.str().empty());
}


int main() 
{
/*
	Database db;
	string command;
	while (getline(cin, command))
 	{
		// Считайте команды с потока ввода и обработайте каждую
	}
*/
	testAddCommandExecute_CorrectCommand_OstreamIsEmpty();
//	testIODatabaseAdapter_Run_InputCorrectCommands_OutputResultOfCommandExecution();
//	testIODatabaseAdapter_Run_InputAddPrintCommands_OutputResultPrintOfOneEvent();
	return 0;
}
