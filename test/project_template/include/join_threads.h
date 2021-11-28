#pragma once

#include <vector>
#include <thread>
#include "utils.h"
namespace Utils
{
    class JoinThreads
    {
    public:
        explicit JoinThreads(std::vector<std::thread>& threads)
            : m_threads(threads)
        {}
        ~JoinThreads()
        {
            LOGF;
            for (size_t i = 0; i < m_threads.size(); ++i)
            {
                if (m_threads[i].joinable())
                    m_threads[i].join();
            }
        }
    private:
        std::vector<std::thread>& m_threads;
    };
} // !Utils