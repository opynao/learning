#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <exception>
//#define INCEXT 0 
#ifdef INCEXT
#include "TaskTreker.h"
#endif

std::map<int,std::string> trace {};
int nnn = 466;
int number = 0;

#define LOGF(x) trace.emplace(++nnn,std::string(__FUNCTION__)+": "+(x))

//std::cerr << __FUNCTION__ << std::endl

/*
class TasksInfo_t:public std::map<TaskStatus,int> 
{
	virtual bool operator == (const std::map<TaskStatus,int>& m)
	{
		LOGF("1");
		return static_cast<std::map<TaskStatus,int>>(*this) == m;
	}
};
*/

using TasksInfo_t = TasksInfo;

std::string to_string(const TaskStatus status)
{
	switch(status)
	{
		case TaskStatus::NEW: return "N";
		case TaskStatus::IN_PROGRESS: return "P";
		case TaskStatus::TESTING: return "T";
		case TaskStatus::DONE: return "D";
	}
}



using personName_t = std::string;

std::vector<TaskStatus> vStatus {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE};

void EraseEmptyElems(TasksInfo&);
void PrintTasksInfo(TasksInfo); 
TasksInfo_t GetUntouchedTasks(TasksInfo&, TasksInfo&);
int CalculateUndoneCases(const TasksInfo&);

//--------------------------CLASS-TEAMTASKS-------------------------------

class TeamTasks 
{
public:
	const TasksInfo& GetPersonTasksInfo(const personName_t&) const;
  
	void AddNewTask(const personName_t&);
  
	std::tuple<TasksInfo_t, TasksInfo_t> PerformPersonTasks(const personName_t&, int);

private:

	std::map<personName_t,TasksInfo> personTask;
};

void TeamTasks::AddNewTask(const personName_t& person)
{
	static int pp = 0;
	static int nn = 0;
	++nn;
	if(pp != number)
	{
		pp = number;
		if(person == "person1")
			LOGF(person + " : " + std::to_string(nn));
		nn = 0;
	}
	auto it = personTask.find(person);
	if(it != personTask.cend())
		it->second[TaskStatus::NEW]++;
	else
	{
		std::map<TaskStatus,int> tasks {{TaskStatus::NEW,1}};
		personTask[person] = tasks;
	}
}

//---------------------GET-PERSON-TASKS-INFO-----------------

const TasksInfo& TeamTasks::GetPersonTasksInfo(const personName_t& person) const
{
	if(person == "person1" )//number == 466)
		LOGF(person);
	if(number == 466)
	{
		std::string msg; // = std::to_string(task_count);
		for(const auto& task : trace)
			msg += ' ' + std::to_string(task.first) + ": " + task.second + '\n';
			throw(std::logic_error(msg));
	}
	return personTask.at(person);
}

//---------------------CALCULATE-UNDONE-CASES---------------
//

int CalculateUndoneCases(const TasksInfo& tasks)
{
	int uc = std::accumulate( std::begin(tasks), std::end(tasks), 0, [] ( const int init, TasksInfo::const_reference second ) -> int 
				{ return second.first != TaskStatus::DONE ? init + second.second : init; }
				) ;
	return uc;
}

//--------------------MOVE-TASKS-------------------------------

TasksInfo_t MoveTasks( TasksInfo& tasks, int task_count )
{
/*	std::string mm = "task_count:" + std::to_string(task_count) + "\n\t{\n";
	for(const auto& task : tasks)
		mm += "\t\t{ " + to_string(task.first) + ", " + std::to_string(task.second) + " }\n";
	mm += "\t}";
	LOGF(mm);
*/	auto itBegin = tasks.begin();
	auto nextStatus = ++std::find( std::cbegin( vStatus ), std::cend( vStatus ), itBegin->first );

	int undoneCases = CalculateUndoneCases(tasks);
	
	if( task_count > undoneCases )
		task_count = undoneCases;
	

	TasksInfo_t updated_tasks;

	int saved_task = itBegin->second;		
	int tasks_on_begin = itBegin->second;
	auto itPrevBegin = itBegin;

	while(task_count)
	{ 
		if(itPrevBegin != itBegin)
		{
		       tasks_on_begin = itBegin->second - saved_task;
		       itPrevBegin = itBegin;
		}
		if(itBegin->second != 0 && saved_task--)
		{
			itBegin->second--;

			tasks[*nextStatus]++;

			updated_tasks[*nextStatus]++;
	
			task_count--;

		}
		else
		{
			saved_task = tasks_on_begin;
			itPrevBegin = itBegin;
			++itBegin;
			++nextStatus;
		}
	} 
	return updated_tasks;	
}

//-----------------------------PERFORM-PERSON-TASKS--------------------------

std::tuple<TasksInfo_t, TasksInfo_t> TeamTasks::PerformPersonTasks(const personName_t& person, int task_count)
{
	auto it = personTask.find(person);
	if(it == personTask.cend())
		return {};
	
	TasksInfo& tasksOfConcretePerson = it->second;
//	int undoneCases = CalculateUndoneCases(tasksOfConcretePerson);
	
	TasksInfo pt = tasksOfConcretePerson;

	TasksInfo_t updated_tasks = MoveTasks( tasksOfConcretePerson, task_count);
	
//	int ud = undoneCases - task_count;
	TasksInfo_t untouched_tasks = GetUntouchedTasks(tasksOfConcretePerson,updated_tasks);
	
	EraseEmptyElems(tasksOfConcretePerson);
	EraseEmptyElems(updated_tasks);
	EraseEmptyElems(untouched_tasks);

	number++;
//	if(++number == 465 || number == 466)
	if(person == "person1")
		LOGF(std::to_string(task_count) + '\n');
	if(number == 466)
	{
	std::string mm = "person: " + person + ", task_count: " + std::to_string(task_count);
	mm += "\n\ts :\n\t{";
	for(const auto& task : pt)
		mm += "\t\t{ " + to_string(task.first) + ", " + std::to_string(task.second) + " }\n";
	mm += "\t}";
	mm += "\n\tu:\n\t{";
	for(const auto& task : updated_tasks)
		mm += "\t\t{ " + to_string(task.first) + ", " + std::to_string(task.second) + " }\n";
	mm += "\t}";
	mm += "\n\tt:\n\t{";
	for(const auto& task : untouched_tasks)
		mm += "\t\t{ " + to_string(task.first) + ", " + std::to_string(task.second) + " }\n";
	mm += "\t}";
	mm += "\n\tr:\n\t{";
	for(const auto& task : tasksOfConcretePerson)
		mm += "\t\t{ " + to_string(task.first) + ", " + std::to_string(task.second) + " }\n";
	mm += "\t}";
	LOGF(mm);

		std::string msg; // = std::to_string(task_count);
		for(const auto& task : trace)
			msg += ' ' + std::to_string(task.first) + ": " + task.second + '\n';
		if(number == 466)
			throw(std::logic_error(msg.c_str()));
	}


	return {updated_tasks,untouched_tasks};
}

//----------------------------END-OF-CLASS-------------------------------
//
//--------------------------NON-MEMEBER-FUNCTIONS------------------------
void PrintTasksInfo(TasksInfo tasks_info) 
{
	std::cout << tasks_info[TaskStatus::NEW] << " new tasks" << 
	", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" << 
	", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
	", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}


void EraseEmptyElems(TasksInfo& tasks)
{
	for( const auto& status : vStatus )
	{
		if( tasks.find( status ) != std::cend( tasks ) && tasks.at( status ) == 0 )
				tasks.erase(status);
	}
}	

TasksInfo_t GetUntouchedTasks(TasksInfo& tasks,TasksInfo& updated_tasks)
{
	TasksInfo_t untouched_tasks;
	for(auto ip = tasks.cbegin(); ip != tasks.cend(); ++ip)
	{
		untouched_tasks[ip->first] = tasks[ip->first] - updated_tasks[ip->first];
	}
	untouched_tasks.erase(TaskStatus::DONE);
	EraseEmptyElems(untouched_tasks);
	return untouched_tasks;
}


//---------------------------------TESTS----------------------------------------
//
//
void testMoveTasks()
{
	TasksInfo tasks
	{
		{ TaskStatus::NEW, 5 }
	};

	const auto upd = MoveTasks( tasks, 3);
	
	TasksInfo result
	{
		{ TaskStatus::NEW, 2},
		{ TaskStatus::IN_PROGRESS, 3 }
	};

	assert( tasks == result );

	TasksInfo updated
	{
		{ TaskStatus::IN_PROGRESS, 3}
	};

	assert( upd == updated );
}



void testUntouchedTasks()
{
	TasksInfo tasks 
	{
		{ TaskStatus::NEW, 5},
		{ TaskStatus::IN_PROGRESS, 2},
		{ TaskStatus::TESTING, 3},
		{ TaskStatus::DONE, 1}
	};
	TasksInfo updated_tasks 
	{
		{ TaskStatus::IN_PROGRESS, 2},
	};
	TasksInfo utTasks = GetUntouchedTasks( tasks, updated_tasks );
	TasksInfo result
	{
		{ TaskStatus::NEW, 5},
		{ TaskStatus::TESTING, 3}
	};
	assert(result == utTasks);
}

void testCourseraFirst()
{
	TasksInfo updated_tasks, untouched_tasks;
	TeamTasks tasks;
	for (int i = 0; i < 3; ++i) 
	{
		tasks.AddNewTask("Ivan");
	}
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	TasksInfo updated_tasks_result 
	{
		{ TaskStatus::IN_PROGRESS, 2},
	};
	TasksInfo untouched_tasks_result
	{
		{ TaskStatus::NEW, 1},
	};
	assert(updated_tasks_result == updated_tasks);
	assert(untouched_tasks_result == untouched_tasks);
	
	
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	updated_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 1},
		{ TaskStatus::TESTING, 1},
	};
	untouched_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 1},
	};
	assert(updated_tasks_result == updated_tasks);
	assert(untouched_tasks_result == untouched_tasks);
}

void testCourseraSecond()
{
	TasksInfo updated_tasks, untouched_tasks;
	TeamTasks tasks;
	for (int i = 0; i < 5; ++i) 
	{
		tasks.AddNewTask("Alice");
	}
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	TasksInfo updated_tasks_result 
	{
		{ TaskStatus::IN_PROGRESS, 5},
	};
	TasksInfo untouched_tasks_result
	{
	};
	assert(updated_tasks_result == updated_tasks);
	assert(untouched_tasks_result == untouched_tasks);

	//---------------------------------------------

	TasksInfo updated_tasks1, untouched_tasks1;
	std::tie(updated_tasks1, untouched_tasks1) = tasks.PerformPersonTasks("Alice", 5);
	updated_tasks_result =
	{
		{ TaskStatus::TESTING, 5},
	};
	untouched_tasks_result =
	{
	};
	assert(updated_tasks_result == updated_tasks1);
	assert(untouched_tasks_result == untouched_tasks1);
	
	//--------------------------------------------------
	
	TasksInfo updated_tasks3, untouched_tasks3;
	std::tie(updated_tasks3, untouched_tasks3) = tasks.PerformPersonTasks("Alice", 1);
	updated_tasks_result =
	{
		{ TaskStatus::DONE, 1},
	};
	untouched_tasks_result =
	{
		{ TaskStatus::TESTING, 4},
	};
	assert(updated_tasks_result == updated_tasks3);
	assert(untouched_tasks_result == untouched_tasks3);
	
	//-----------------------------------------------

	for (int i = 0; i < 5; ++i) 
	{
		tasks.AddNewTask("Alice");
	}

	//-------------------------------------------------
	
	TasksInfo updated_tasks4, untouched_tasks4;
	std::tie(updated_tasks4, untouched_tasks4) = tasks.PerformPersonTasks("Alice", 2);

	updated_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 2},
	};
	untouched_tasks_result =
	{
		{ TaskStatus::NEW, 3},
		{ TaskStatus::TESTING, 4},
	};
	assert(updated_tasks_result == updated_tasks4);
	assert(untouched_tasks_result == untouched_tasks4);
	//--------------------------------------------------
	
	
	TasksInfo tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	TasksInfo tasksOfConcretePerson_result
	{
		{ TaskStatus::NEW, 3},
		{ TaskStatus::IN_PROGRESS, 2},
		{ TaskStatus::TESTING, 4},
		{ TaskStatus::DONE, 1}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);
	//-------------------------------------------------

	TasksInfo updated_tasks5, untouched_tasks5;
	std::tie(updated_tasks5, untouched_tasks5) = tasks.PerformPersonTasks("Alice", 4);

	updated_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 3},
		{ TaskStatus::TESTING, 1},
	};
	untouched_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 1},
		{ TaskStatus::TESTING, 4},
	};
	assert(updated_tasks_result == updated_tasks5);
	assert(untouched_tasks_result == untouched_tasks5);
	//---------------------------------------------

	tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	tasksOfConcretePerson_result =
	{
		{ TaskStatus::IN_PROGRESS, 4},
		{ TaskStatus::TESTING, 5},
		{ TaskStatus::DONE, 1}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);
}

void testCourseraThird()
{
	TasksInfo updated_tasks, untouched_tasks;
	TeamTasks tasks;
	for (int i = 0; i < 4; ++i) 
	{
		tasks.AddNewTask("Alice");
	}
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
	for (int i = 0; i < 4; ++i) 
	{
		tasks.AddNewTask("Alice");
	}
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 10);

	TasksInfo tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	TasksInfo tasksOfConcretePerson_result
	{
		{ TaskStatus::IN_PROGRESS, 2},
		{ TaskStatus::TESTING, 2},
		{ TaskStatus::DONE, 4}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);
}


void testCourseraForth()
{
	TeamTasks tasks;
	TasksInfo updated_tasks, untouched_tasks;
	tasks.AddNewTask("Jack");
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    	TasksInfo updated_tasks_result 
	{
		{ TaskStatus::IN_PROGRESS, 1},
	};
	TasksInfo untouched_tasks_result
	{
	};
	assert(updated_tasks_result == updated_tasks);
	assert(untouched_tasks_result == untouched_tasks);



	tasks.AddNewTask("Jack");
	TasksInfo updated_tasks2, untouched_tasks2;
	std::tie(updated_tasks2, untouched_tasks2) = tasks.PerformPersonTasks("Jack", 2);
	updated_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 1},
		{ TaskStatus::TESTING, 1},
	};
	untouched_tasks_result =
	{
	};
	assert(updated_tasks_result == updated_tasks2);
	assert(untouched_tasks_result == untouched_tasks2);


	tasks.AddNewTask("Jack");
	TasksInfo tasksOfConcretePerson = tasks.GetPersonTasksInfo("Jack");
	TasksInfo tasksOfConcretePerson_result
	{
		{ TaskStatus::NEW, 1},
		{ TaskStatus::IN_PROGRESS, 1},
		{ TaskStatus::TESTING, 1},
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);


	TasksInfo updated_tasks3, untouched_tasks3;
	std::tie(updated_tasks3, untouched_tasks3) = tasks.PerformPersonTasks("Jack", 3);
	updated_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 1},
		{ TaskStatus::TESTING, 1},
		{ TaskStatus::DONE, 1},
	};
	untouched_tasks_result =
	{
	};
	assert(updated_tasks_result == updated_tasks3);
	assert(untouched_tasks_result == untouched_tasks3);
}

void testCourseraFifth()
{
	TeamTasks tasks;
	TasksInfo updated_tasks, untouched_tasks;
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 1);
    	TasksInfo updated_tasks_result 
	{
	};
	TasksInfo untouched_tasks_result
	{
	};
	assert(updated_tasks_result == updated_tasks);
	assert(untouched_tasks_result == untouched_tasks);
}

void testCourseraSixth()
{
	TeamTasks tasks;
	TasksInfo updated_tasks, untouched_tasks;
	for (int i = 0; i < 5; ++i) 
	{
		tasks.AddNewTask("Alice");
	}
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	TasksInfo updated_tasks_result 
	{
		{ TaskStatus::IN_PROGRESS, 5},
	};
	TasksInfo untouched_tasks_result
	{
	};
	assert(updated_tasks_result == updated_tasks);
	assert(untouched_tasks_result == untouched_tasks);

	//---------------------------------------------

	TasksInfo updated_tasks1, untouched_tasks1;
	std::tie(updated_tasks1, untouched_tasks1) = tasks.PerformPersonTasks("Alice", 5);
	updated_tasks_result =
	{
		{ TaskStatus::TESTING, 5},
	};
	untouched_tasks_result =
	{
	};
	assert(updated_tasks_result == updated_tasks1);
	assert(untouched_tasks_result == untouched_tasks1);
	
	//--------------------------------------------------
	
	TasksInfo updated_tasks3, untouched_tasks3;
	std::tie(updated_tasks3, untouched_tasks3) = tasks.PerformPersonTasks("Alice", 1);
	updated_tasks_result =
	{
		{ TaskStatus::DONE, 1},
	};
	untouched_tasks_result =
	{
		{ TaskStatus::TESTING, 4},
	};
	assert(updated_tasks_result == updated_tasks3);
	assert(untouched_tasks_result == untouched_tasks3);
	
	//-----------------------------------------------
	
	for (int i = 0; i < 5; ++i) 
	{
		tasks.AddNewTask("Alice");
	}


	TasksInfo updated_tasks4, untouched_tasks4;
	std::tie(updated_tasks4, untouched_tasks4) = tasks.PerformPersonTasks("Alice", 2);

	updated_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 2},
	};
	untouched_tasks_result =
	{
		{ TaskStatus::NEW, 3},
		{ TaskStatus::TESTING, 4},
	};
	assert(updated_tasks_result == updated_tasks4);
	assert(untouched_tasks_result == untouched_tasks4);
	//--------------------------------------------------
	
	
	TasksInfo tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	TasksInfo tasksOfConcretePerson_result
	{
		{ TaskStatus::NEW, 3},
		{ TaskStatus::IN_PROGRESS, 2},
		{ TaskStatus::TESTING, 4},
		{ TaskStatus::DONE, 1}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);
	//-------------------------------------------------

	TasksInfo updated_tasks5, untouched_tasks5;
	std::tie(updated_tasks5, untouched_tasks5) = tasks.PerformPersonTasks("Alice", 4);

	updated_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 3},
		{ TaskStatus::TESTING, 1},
	};
	untouched_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 1},
		{ TaskStatus::TESTING, 4},
	};
	assert(updated_tasks_result == updated_tasks5);
	assert(untouched_tasks_result == untouched_tasks5);
	//---------------------------------------------

	tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	tasksOfConcretePerson_result =
	{
		{ TaskStatus::IN_PROGRESS, 4},
		{ TaskStatus::TESTING, 5},
		{ TaskStatus::DONE, 1}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);

  //-------------------------------------------TEST-UNTOUCHED-DOESNT-RETURN-DONE----------------- 
	TasksInfo updated_tasks6, untouched_tasks6;
	std::tie(updated_tasks6, untouched_tasks6) = tasks.PerformPersonTasks("Alice", 5);

	updated_tasks_result =
	{
		{ TaskStatus::TESTING, 4},
		{ TaskStatus::DONE, 1}
	};
	untouched_tasks_result =
	{
		{ TaskStatus::TESTING, 4},
	};
	assert(updated_tasks_result == updated_tasks6);
	assert(untouched_tasks_result == untouched_tasks6);
	
//---------------------------------------------------------------
	tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	tasksOfConcretePerson_result =
	{
		{ TaskStatus::TESTING, 8},
		{ TaskStatus::DONE, 2}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);

  //------------------------------------------------------------ 
	TasksInfo updated_tasks7, untouched_tasks7;
	std::tie(updated_tasks7, untouched_tasks7) = tasks.PerformPersonTasks("Alice", 10);

	updated_tasks_result =
	{
		{ TaskStatus::DONE, 8}
	};
	untouched_tasks_result =
	{
	};
	assert(updated_tasks_result == updated_tasks7);
	assert(untouched_tasks_result == untouched_tasks7);
	
//---------------------------------------------------------------

	tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	tasksOfConcretePerson_result =
	{
		{ TaskStatus::DONE, 10}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);

  //------------------------------------------------------------ 
	TasksInfo updated_tasks8, untouched_tasks8;
	std::tie(updated_tasks8, untouched_tasks8) = tasks.PerformPersonTasks("Alice", 10);

	updated_tasks_result =
	{
	};
	untouched_tasks_result =
	{
	};
	assert(updated_tasks_result == updated_tasks8);
	assert(untouched_tasks_result == untouched_tasks8);
	
//---------------------------------------------------------------
	tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	tasksOfConcretePerson_result =
	{
		{ TaskStatus::DONE, 10}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);

  //------------------------------------------------------------ 

	tasks.AddNewTask("Alice");
	tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	tasksOfConcretePerson_result =
	{
		{ TaskStatus::NEW, 1},
		{ TaskStatus::DONE, 10}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);

  //------------------------------------------------------------ 
	TasksInfo updated_tasks9, untouched_tasks9;
	std::tie(updated_tasks9, untouched_tasks9) = tasks.PerformPersonTasks("Alice", 2);

	updated_tasks_result =
	{
		{ TaskStatus::IN_PROGRESS, 1}
	};
	untouched_tasks_result =
	{
	};
	assert(updated_tasks_result == updated_tasks9);
	assert(untouched_tasks_result == untouched_tasks9);
	
//---------------------------------------------------------------
	tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
	tasksOfConcretePerson_result =
	{
		{ TaskStatus::IN_PROGRESS, 1},
		{ TaskStatus::DONE, 10}
	};
	assert(tasksOfConcretePerson_result == tasksOfConcretePerson);
}

void testCourseraSeventh()
{
	TeamTasks tasks;
	TasksInfo updated_tasks, untouched_tasks;
	for (int i = 0; i < 5; ++i) 
	{
		tasks.AddNewTask("Alice");
	}
	std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 0);
	TasksInfo updated_tasks_result 
	{
	};
	TasksInfo untouched_tasks_result
	{
		{ TaskStatus::NEW, 5},
	};
	assert(updated_tasks_result == updated_tasks);
	assert(untouched_tasks_result == untouched_tasks);
}

	
void RunAllTests()
{
	testMoveTasks();
	testUntouchedTasks();
	testCourseraFirst();
	testCourseraSecond();
	testCourseraThird();
	testCourseraForth();
	testCourseraFifth();
	testCourseraSixth();
	testCourseraSeventh();
}



int main()
{
	RunAllTests();
	return 0;
}

