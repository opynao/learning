#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>
#include <atomic>
#include <vector>

#include "queue.h"
#include "join_threads.h"
#include "utils.h"

namespace Utils
{

    class ThreadPool
    {
    public:

        ThreadPool(int threads) : shutdown_(false)
        {
            // Create the specified number of threads
            threads_.reserve(static_cast<size_t>(threads));
            for (int i = 0; i < threads; ++i)
                threads_.emplace_back(std::bind(&ThreadPool::threadEntry, this, i));
        }

        ~ThreadPool()
        {
            {
                // Unblock any threads and tell them to stop
                std::unique_lock <std::mutex> l(lock_);

                shutdown_ = true;
                condVar_.notify_all();
            }

            // Wait for all threads to stop
            std::cerr << "Joining threads" << std::endl;
            for (auto& thread : threads_)
                thread.join();
        }

        void doJob(std::function <void(void)> func)
        {
            // Place a job on the queu and unblock a thread
            std::unique_lock <std::mutex> l(lock_);

            // jobs_.emplace(std::move(func));
            jobs_.Push(func);

            condVar_.notify_one();
        }

    protected:

        void threadEntry(int i)
        {
            std::function <void(void)> job;

            while (1)
            {
                {
                    std::unique_lock <std::mutex> l(lock_);

                    //                    while (!shutdown_ && jobs_.empty())
                    while (!shutdown_ && jobs_.IsEmpty())

                        condVar_.wait(l);

                    // if (jobs_.empty())
                    if (jobs_.IsEmpty())

                    {
                        // No jobs to do and we are shutting down
                        std::cerr << "Thread " << i << " terminates" << std::endl;
                        return;
                    }

                    std::cerr << "Thread " << i << " does a job" << std::endl;
                    // job = std::move(jobs_.front());
                    // jobs_.pop();
                    jobs_.TryPop(job);
                }

                // Do the job without holding any locks
                job();
            }

        }

        std::mutex lock_;
        std::condition_variable condVar_;
        bool shutdown_;
        // std::queue <std::function <void(void)>> jobs_;
        ThreadsafeQueue <std::function <void(void)>> jobs_;
        std::vector <std::thread> threads_;
    };

    // class ThreadPool
    // {
    // public:
    //     ThreadPool(const size_t threadCount)
    //         : m_done(false)
    //         , m_joiner(m_threads)
    //     {
    //         // const size_t threadCount = std::thread::hardware_concurrency();
    //         try
    //         {
    //             LOGF;
    //             for (size_t i = 0; i < threadCount; ++i)
    //                 m_threads.push_back(std::thread(&ThreadPool::DoWork, this, i));
    //         }
    //         catch (...)
    //         {
    //             m_done = true;
    //             throw;
    //         }
    //     }

    //     ~ThreadPool()
    //     {
    //         LOGF;
    //         m_done = true;
    //     }

    //     //        m_Condition.notify_all();
    //     template<typename... Args>
    //     void AddTask(Args&&... args)
    //     {
    //         LOGF;
    //         m_tasksPool.Push(std::bind(std::forward<Args>(args)...));
    //     }
    // private:
    //     void DoWork(size_t threadId)
    //     {
    //         LOGF;
    //         while (!m_done)
    //         {
    //             std::function<void()> task;
    //             if (m_tasksPool.TryPop(task))
    //             {
    //                 std::cout << "Thread " << threadId << " does a job" << std::endl;
    //                 task();
    //             }
    //             // else
    //             //     std::this_thread::yield();
    //         }
    //     }
    // private:
    //     std::atomic_bool m_done;
    //     ThreadsafeQueue<std::function<void()>> m_tasksPool;
    //     std::vector<std::thread> m_threads;
    //     JoinThreads m_joiner;
    // };
} // !Utils