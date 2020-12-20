#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <exception>
#include "task_treker.h"

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



