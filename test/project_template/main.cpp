#include <vector>
#include <thread>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <chrono>

#include "queue.h"
#include "pool.h"
#include "profile.h"
#include "utils.h"

namespace fs = std::filesystem;
using namespace Utils;

auto c = [](const std::string& str)
{
    std::ofstream ofs(str + "new");
    for (int i = 0; i != 10; ++i)
    {
        std::ifstream ifs(str);
        char buf[4096];
        while (ifs.read(buf, 4096))
            ofs.write(buf, 4096);
    }
};

auto l = [](const std::string& str)
{
    std::cout << "Start of copy " << str << std::endl;
    fs::copy_file(str, "/tmp/copy_files/" + str);
    std::cout << "End of copy " << str << std::endl;
};

// auto k = [](ThreadsafeQueue<std::string>& q)
// {
//     std::cout << "Start of copy " << str << std::endl;
//     fs::copy_file(str, "/tmp/copy_files/" + str);
//     std::cout << "End of copy " << str << std::endl;
// };

constexpr auto fnames = { "libboost_test_exec_monitor.anew",
                            "libLLVM-12.so.1new",
                            "libLLVM-13.so.1new",
                            "librsvg-2.so.2.47.0new",
                            "libvulkan_intel.sonew",
                            "libz3.so.4new",
                            "libclang-13.so.13.0.0new",
                            "libicudata.anew" };
using namespace std::chrono_literals;

int main()
{
    // Create two threads
    ThreadPool p(8);
    LOGF;
    //  ThreadsafeQueue<std::string> queue;
    LOG_DURATION("copy");

    // while (!queue.IsEmpty())
    {
        for (auto& i : fnames)
        {
            // p.doJob(std::bind(l, i));
            p.doJob([i] { c(i); });

            LOGF;
            //        queue.Push(i);
            // std::this_thread::sleep_for(200ms);
        }
    }
}