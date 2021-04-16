#pragma once
#include <mutex>
#include <algorithm>
#include <iostream>
// Реализуйте шаблон Synchronized<T>.
// Метод GetAccess должен возвращать структуру, в которой есть поле T& value.

template <typename T>
class Synchronized
{
public:
    explicit Synchronized(T initial = T())
        : value(std::move(initial))
    {
    }

    struct Access
    {
        T &ref_to_value;
        std::lock_guard<std::mutex> guard;
        Access(T &r, std::mutex &m)
            : ref_to_value{r}, guard(m)
        {
            //    std::cerr << "LOCK " << std::endl;
        }
        ~Access()
        {
            //    std::cerr << "UNLOCK " <<  std::endl;
        }
    };

    Access GetAccess()
    {
        return Access(value, m);
    }

private:
    T value;
    std::mutex m;
};
