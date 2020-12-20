#include "non_memeber.h"
#include "task_treker.h"

#include <iostream>
#include <map>

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



