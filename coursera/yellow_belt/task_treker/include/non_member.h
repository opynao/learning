#pragma once
#include "task_treker.h"

void EraseEmptyElems(TasksInfo&);
void PrintTasksInfo(TasksInfo); 
TasksInfo_t GetUntouchedTasks(TasksInfo&, TasksInfo&);
int CalculateUndoneCases(const TasksInfo&);


