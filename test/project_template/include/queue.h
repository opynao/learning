#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>
#include <functional>

#include "utils.h"

namespace Utils
{
    template <typename T>
    class ThreadsafeQueue
    {
    public:
        void Push(T new_value)
        {
            if constexpr (std::is_same_v<T, std::string>)
                std::cout << "Push new file " << new_value << std::endl;
            LOGF;
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(std::move(new_value));
            data_cond.notify_all();
        }
        void WaitPop(const T& value)
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [this] { return !data_queue.empty(); });
            value = std::move(data_queue.front());
            data_queue.pop();
        }
        std::shared_ptr<T> WaitPop()
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [this]
                { return !data_queue.empty(); });
            std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
            data_queue.pop();
            return res;
        }
        bool TryPop(T& value)
        {
            std::lock_guard<std::mutex> lk(mut);
            if (data_queue.empty())
                return false;
            value = std::move(data_queue.front());
            data_queue.pop();
            return true;
        }
        std::shared_ptr<T> TryPop()
        {
            std::lock_guard<std::mutex> lk(mut);
            if (data_queue.empty())
                return std::shared_ptr<T>();
            std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
            data_queue.pop();
            return res;
        }
        bool IsEmpty() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data_queue.empty();
        }

    private:
        mutable std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_cond;
    };
} // !Utils