#include "gtest/gtest.h"
#include "team_tasks.h"
#include "print_tasks.h"

TEST(Basic, Test1)
{
    TasksInfo updated_tasks, untouched_tasks;
    TeamTasks tasks;
    for (int i = 0; i < 3; ++i)
        tasks.AddNewTask("Ivan");

    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);

    TasksInfo updated_tasks_result{
        {TaskStatus::IN_PROGRESS, 2},
    };

    TasksInfo untouched_tasks_result{
        {TaskStatus::NEW, 1},
    };
    
    EXPECT_EQ(updated_tasks_result, updated_tasks);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks);

    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    updated_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 1},
            {TaskStatus::TESTING, 1},
        };
    untouched_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 1},
        };
    EXPECT_EQ(updated_tasks_result, updated_tasks);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks);
}

TEST(Basic, Test2)
{
    TasksInfo updated_tasks, untouched_tasks;
    TeamTasks tasks;
    for (int i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }
    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    TasksInfo updated_tasks_result{
        {TaskStatus::IN_PROGRESS, 5},
    };
    TasksInfo untouched_tasks_result{};
    EXPECT_EQ(updated_tasks_result, updated_tasks);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks);

    //---------------------------------------------

    TasksInfo updated_tasks1, untouched_tasks1;
    std::tie(updated_tasks1, untouched_tasks1) = tasks.PerformPersonTasks("Alice", 5);
    updated_tasks_result =
        {
            {TaskStatus::TESTING, 5},
        };
    untouched_tasks_result =
        {};
    EXPECT_EQ(updated_tasks_result, updated_tasks1);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks1);

    //--------------------------------------------------

    TasksInfo updated_tasks3, untouched_tasks3;
    std::tie(updated_tasks3, untouched_tasks3) = tasks.PerformPersonTasks("Alice", 1);
    updated_tasks_result =
        {
            {TaskStatus::DONE, 1},
        };
    untouched_tasks_result =
        {
            {TaskStatus::TESTING, 4},
        };
    EXPECT_EQ(updated_tasks_result, updated_tasks3);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks3);

    //-----------------------------------------------

    for (int i = 0; i < 5; ++i)
        tasks.AddNewTask("Alice");

    //-------------------------------------------------

    TasksInfo updated_tasks4, untouched_tasks4;
    std::tie(updated_tasks4, untouched_tasks4) = tasks.PerformPersonTasks("Alice", 2);

    updated_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 2},
        };
    untouched_tasks_result =
        {
            {TaskStatus::NEW, 3},
            {TaskStatus::TESTING, 4},
        };
    EXPECT_EQ(updated_tasks_result, updated_tasks4);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks4);
    //--------------------------------------------------

    TasksInfo tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    TasksInfo tasksOfConcretePerson_result{
        {TaskStatus::NEW, 3},
        {TaskStatus::IN_PROGRESS, 2},
        {TaskStatus::TESTING, 4},
        {TaskStatus::DONE, 1}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);
    //-------------------------------------------------

    TasksInfo updated_tasks5, untouched_tasks5;
    std::tie(updated_tasks5, untouched_tasks5) = tasks.PerformPersonTasks("Alice", 4);

    updated_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 3},
            {TaskStatus::TESTING, 1},
        };
    untouched_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 1},
            {TaskStatus::TESTING, 4},
        };
    EXPECT_EQ(updated_tasks_result, updated_tasks5);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks5);
    //---------------------------------------------

    tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    tasksOfConcretePerson_result =
        {
            {TaskStatus::IN_PROGRESS, 4},
            {TaskStatus::TESTING, 5},
            {TaskStatus::DONE, 1}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);
}

TEST(Basic, Test3)
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
    TasksInfo tasksOfConcretePerson_result{
        {TaskStatus::IN_PROGRESS, 2},
        {TaskStatus::TESTING, 2},
        {TaskStatus::DONE, 4}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);
}

TEST(Basic, Test4)
{
    TeamTasks tasks;
    TasksInfo updated_tasks, untouched_tasks;
    tasks.AddNewTask("Jack");
    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    TasksInfo updated_tasks_result{
        {TaskStatus::IN_PROGRESS, 1},
    };
    TasksInfo untouched_tasks_result{};
    EXPECT_EQ(updated_tasks_result, updated_tasks);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks);

    tasks.AddNewTask("Jack");
    TasksInfo updated_tasks2, untouched_tasks2;
    std::tie(updated_tasks2, untouched_tasks2) = tasks.PerformPersonTasks("Jack", 2);
    updated_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 1},
            {TaskStatus::TESTING, 1},
        };
    untouched_tasks_result =
        {};
    EXPECT_EQ(updated_tasks_result, updated_tasks2);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks2);

    tasks.AddNewTask("Jack");
    TasksInfo tasksOfConcretePerson = tasks.GetPersonTasksInfo("Jack");
    TasksInfo tasksOfConcretePerson_result{
        {TaskStatus::NEW, 1},
        {TaskStatus::IN_PROGRESS, 1},
        {TaskStatus::TESTING, 1},
    };
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);

    TasksInfo updated_tasks3, untouched_tasks3;
    std::tie(updated_tasks3, untouched_tasks3) = tasks.PerformPersonTasks("Jack", 3);
    updated_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 1},
            {TaskStatus::TESTING, 1},
            {TaskStatus::DONE, 1},
        };
    untouched_tasks_result =
        {};
    EXPECT_EQ(updated_tasks_result, updated_tasks3);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks3);
}

TEST(Basic, Test5)
{
    TeamTasks tasks;
    TasksInfo updated_tasks, untouched_tasks;
    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 1);
    TasksInfo updated_tasks_result{};
    TasksInfo untouched_tasks_result{};
    EXPECT_EQ(updated_tasks_result, updated_tasks);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks);
}

TEST(Basic, Test6)
{
    TeamTasks tasks;
    TasksInfo updated_tasks, untouched_tasks;
    for (int i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }
    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    TasksInfo updated_tasks_result{
        {TaskStatus::IN_PROGRESS, 5},
    };
    TasksInfo untouched_tasks_result{};
    EXPECT_EQ(updated_tasks_result, updated_tasks);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks);

    //---------------------------------------------

    TasksInfo updated_tasks1, untouched_tasks1;
    std::tie(updated_tasks1, untouched_tasks1) = tasks.PerformPersonTasks("Alice", 5);
    updated_tasks_result =
        {
            {TaskStatus::TESTING, 5},
        };
    untouched_tasks_result =
        {};
    EXPECT_EQ(updated_tasks_result, updated_tasks1);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks1);

    //--------------------------------------------------

    TasksInfo updated_tasks3, untouched_tasks3;
    std::tie(updated_tasks3, untouched_tasks3) = tasks.PerformPersonTasks("Alice", 1);
    updated_tasks_result =
        {
            {TaskStatus::DONE, 1},
        };
    untouched_tasks_result =
        {
            {TaskStatus::TESTING, 4},
        };
    EXPECT_EQ(updated_tasks_result, updated_tasks3);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks3);

    //-----------------------------------------------

    for (int i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }

    TasksInfo updated_tasks4, untouched_tasks4;
    std::tie(updated_tasks4, untouched_tasks4) = tasks.PerformPersonTasks("Alice", 2);

    updated_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 2},
        };
    untouched_tasks_result =
        {
            {TaskStatus::NEW, 3},
            {TaskStatus::TESTING, 4},
        };
    EXPECT_EQ(updated_tasks_result, updated_tasks4);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks4);
    //--------------------------------------------------

    TasksInfo tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    TasksInfo tasksOfConcretePerson_result{
        {TaskStatus::NEW, 3},
        {TaskStatus::IN_PROGRESS, 2},
        {TaskStatus::TESTING, 4},
        {TaskStatus::DONE, 1}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);
    //-------------------------------------------------

    TasksInfo updated_tasks5, untouched_tasks5;
    std::tie(updated_tasks5, untouched_tasks5) = tasks.PerformPersonTasks("Alice", 4);

    updated_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 3},
            {TaskStatus::TESTING, 1},
        };
    untouched_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 1},
            {TaskStatus::TESTING, 4},
        };
    EXPECT_EQ(updated_tasks_result, updated_tasks5);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks5);
    //---------------------------------------------

    tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    tasksOfConcretePerson_result =
        {
            {TaskStatus::IN_PROGRESS, 4},
            {TaskStatus::TESTING, 5},
            {TaskStatus::DONE, 1}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);

    //-------------------------------------------TEST-UNTOUCHED-DOESNT-RETURN-DONE-----------------
    TasksInfo updated_tasks6, untouched_tasks6;
    std::tie(updated_tasks6, untouched_tasks6) = tasks.PerformPersonTasks("Alice", 5);

    updated_tasks_result =
        {
            {TaskStatus::TESTING, 4},
            {TaskStatus::DONE, 1}};
    untouched_tasks_result =
        {
            {TaskStatus::TESTING, 4},
        };
    EXPECT_EQ(updated_tasks_result, updated_tasks6);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks6);

    //---------------------------------------------------------------
    tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    tasksOfConcretePerson_result =
        {
            {TaskStatus::TESTING, 8},
            {TaskStatus::DONE, 2}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);

    //------------------------------------------------------------
    TasksInfo updated_tasks7, untouched_tasks7;
    std::tie(updated_tasks7, untouched_tasks7) = tasks.PerformPersonTasks("Alice", 10);

    updated_tasks_result =
        {
            {TaskStatus::DONE, 8}};
    untouched_tasks_result =
        {};
    EXPECT_EQ(updated_tasks_result, updated_tasks7);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks7);

    //---------------------------------------------------------------

    tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    tasksOfConcretePerson_result =
        {
            {TaskStatus::DONE, 10}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);

    //------------------------------------------------------------
    TasksInfo updated_tasks8, untouched_tasks8;
    std::tie(updated_tasks8, untouched_tasks8) = tasks.PerformPersonTasks("Alice", 10);

    updated_tasks_result =
        {};
    untouched_tasks_result =
        {};
    EXPECT_EQ(updated_tasks_result, updated_tasks8);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks8);

    //---------------------------------------------------------------
    tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    tasksOfConcretePerson_result =
        {
            {TaskStatus::DONE, 10}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);

    //------------------------------------------------------------

    tasks.AddNewTask("Alice");
    tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    tasksOfConcretePerson_result =
        {
            {TaskStatus::NEW, 1},
            {TaskStatus::DONE, 10}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);

    //------------------------------------------------------------
    TasksInfo updated_tasks9, untouched_tasks9;
    std::tie(updated_tasks9, untouched_tasks9) = tasks.PerformPersonTasks("Alice", 2);

    updated_tasks_result =
        {
            {TaskStatus::IN_PROGRESS, 1}};
    untouched_tasks_result =
        {};
    EXPECT_EQ(updated_tasks_result, updated_tasks9);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks9);

    //---------------------------------------------------------------
    tasksOfConcretePerson = tasks.GetPersonTasksInfo("Alice");
    tasksOfConcretePerson_result =
        {
            {TaskStatus::IN_PROGRESS, 1},
            {TaskStatus::DONE, 10}};
    EXPECT_EQ(tasksOfConcretePerson_result, tasksOfConcretePerson);
}

TEST(Basic, Test7)
{
    TeamTasks tasks;
    TasksInfo updated_tasks, untouched_tasks;
    for (int i = 0; i < 5; ++i)
    {
        tasks.AddNewTask("Alice");
    }
    std::tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 0);
    TasksInfo updated_tasks_result{};
    TasksInfo untouched_tasks_result{
        {TaskStatus::NEW, 5},
    };
    EXPECT_EQ(updated_tasks_result, updated_tasks);
    EXPECT_EQ(untouched_tasks_result, untouched_tasks);
}