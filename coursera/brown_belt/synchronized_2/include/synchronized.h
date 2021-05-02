//#pragma once
#include <mutex>

template <typename T>
class Synchronized
{
private:
    struct Access
    {
        T &ref_to_value;
        std::lock_guard<std::mutex> m;
    };
    struct AccessConst
    {
        const T &ref_to_value;
        std::lock_guard<std::mutex> m;
    };

public:
    explicit Synchronized(T initial = T())
        : value{initial}
    {
    }

    Access GetAccess()
    {
        return {value, std::lock_guard(m)};
    }
    AccessConst GetAccess() const
    {
        return {value, std::lock_guard(m)};
    }

private:
    T value;
    mutable std::mutex m;
};
