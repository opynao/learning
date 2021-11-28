#include <semaphore>
#include <thread>
#include <vector>
#include "utils.h"

std::binary_semaphore signalDataProcess(1);
int counter = 10;
std::mutex m;

void ProcessData()
{
    LOG("Task <Process Data> created");
    signalDataProcess.acquire();
    LOGF;
    PR(signalDataProcess.max());
    while (counter != 0)
    {
        // .. some  logic
        m.lock();
        --counter;
        m.unlock();
        PR(counter);
        if (counter == 0)
        {
            signalDataProcess.release();
            //signalDataProcess.release(8);
            //return;
        }
    }
    signalDataProcess.release();
}

int main()
{
    std::vector<std::jthread> v;
    auto numberOfThreads = std::thread::hardware_concurrency();
    for (; numberOfThreads > 0; --numberOfThreads)
        v.emplace_back([]
                       { ProcessData(); });
}