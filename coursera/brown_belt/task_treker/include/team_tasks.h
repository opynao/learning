#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include <tuple>

enum class TaskStatus
{
    NEW,         // новая
    IN_PROGRESS, // в разработке
    TESTING,     // на тестировании
    DONE         // завершена
};

using TasksInfo = std::map<TaskStatus, int>;
using updatedTasks_t = TasksInfo;
using untouchedTasks_t = TasksInfo;
using personName_t = std::string;

class TeamTasks
{
public:
    const TasksInfo &GetPersonTasksInfo(const personName_t &person) const;

    void AddNewTask(const personName_t &person);

    std::tuple<updatedTasks_t, untouchedTasks_t> PerformPersonTasks(
        const personName_t &person, int task_count);

private:
    untouchedTasks_t GetUntouchedTasks(TasksInfo &, updatedTasks_t &);
    updatedTasks_t GetUpdatedTasks(TasksInfo &, int);
    void EraseEmptyTasks(TasksInfo &);
    TaskStatus Next(TaskStatus status);

private:
    std::unordered_map<personName_t, TasksInfo> personTasks;
};
