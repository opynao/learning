#include "team_tasks.h"
#include "utils.h"

#include <algorithm>

const TasksInfo &TeamTasks::GetPersonTasksInfo(const std::string &person) const
{
    return personTasks.at(person);
}

void TeamTasks::AddNewTask(const std::string &person)
{
    ++personTasks[person][TaskStatus::NEW];
}

TaskStatus TeamTasks::Next(TaskStatus status)
{
    return static_cast<TaskStatus>(static_cast<int>(status) + 1);
}

updatedTasks_t TeamTasks::GetUpdatedTasks(TasksInfo &tasksConcretePerson, int task_count)
{
    updatedTasks_t updated_tasks;

    for (TaskStatus status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status))
    {
        // Считаем обновлённые
        updated_tasks[Next(status)] = std::min(task_count, tasksConcretePerson[status]);
        // Считаем, сколько осталось обновить
        task_count -= updated_tasks[Next(status)];
    }

    return updated_tasks;
}

void TeamTasks::EraseEmptyTasks(TasksInfo &tasks)
{
    for (auto it = tasks.cbegin(); it != tasks.cend();)
        it->second == 0 ? it = tasks.erase(it) : ++it;
}

untouchedTasks_t TeamTasks::GetUntouchedTasks(TasksInfo &tasksConcretePerson, TasksInfo &updated_tasks)
{
    untouchedTasks_t untouched_tasks;
    for (TaskStatus status = TaskStatus::NEW;
         status != TaskStatus::DONE;
         status = Next(status))
    {
        untouched_tasks[status] = tasksConcretePerson[status] - updated_tasks[Next(status)];
        tasksConcretePerson[status] += updated_tasks[status] - updated_tasks[Next(status)];
    }
    // По условию, DONE задачи не нужно возвращать в не обновлённых задачах
    tasksConcretePerson[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

    untouched_tasks.erase(TaskStatus::DONE);

    return untouched_tasks;
}

std::tuple<updatedTasks_t, untouchedTasks_t> TeamTasks::PerformPersonTasks(
    const std::string &person, int task_count)
{
    TasksInfo &tasksConcretePerson = personTasks[person];
    updatedTasks_t updated_tasks = GetUpdatedTasks(tasksConcretePerson, task_count);
    untouchedTasks_t untouched_tasks = GetUntouchedTasks(tasksConcretePerson, updated_tasks);

    EraseEmptyTasks(tasksConcretePerson);
    EraseEmptyTasks(updated_tasks);
    EraseEmptyTasks(untouched_tasks);

    return {updated_tasks, untouched_tasks};
}