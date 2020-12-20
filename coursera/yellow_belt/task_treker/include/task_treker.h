#pragma once

enum class TaskStatus
{
	NEW ,          
	IN_PROGRESS ,  
	TESTING ,     
	DONE         
};

using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks 
{
public:
	const TasksInfo& GetPersonTasksInfo(const personName_t&) const;
  
	void AddNewTask(const personName_t&);
  
	std::tuple<TasksInfo_t, TasksInfo_t> PerformPersonTasks(const personName_t&, int);

private:

	std::map<personName_t,TasksInfo> personTask;
};


