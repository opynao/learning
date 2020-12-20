#include "task_treker.h"

#include <cassert>
#include <tuple>


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
