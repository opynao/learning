#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace std::chrono;

class LogDuration
{
public:
  using FunctionCallInfo = std::vector<size_t>;

public:
  explicit LogDuration(const string &msg, std::map<std::string, FunctionCallInfo> &m)
      : message(msg + ": "), start(steady_clock::now()), m_{m}
  {
  }

  ~LogDuration()
  {
    auto finish = steady_clock::now();
    auto dur = finish - start;
    m_[message].push_back(duration_cast<milliseconds>(dur).count());
    /*cerr << message
                duration_cast<milliseconds>(dur)
                    .count()
         << " ms" << endl;
    */
  }

private:
  string message;
  steady_clock::time_point start;
  std::map<std::string, FunctionCallInfo> &m_;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__){message};

#define LOG_DURATION_F 
//LogDuration(std::string(__FUNCTION__),logDurationMap)

#define LOG_DURATION_INIT 
//static std::map<std::string, LogDuration::FunctionCallInfo> logDurationMap

#define LOG_DURATION_SHOW 
             \
//  for (const auto &i : logDurationMap) \
//    std::cerr << i.first << ":\t\t\t\t" << i.second.size() << "\t\t" << std::accumulate(i.second.cbegin(), i.second.cend(), 0) / i.second.size() << "\t\t" << std::accumulate(i.second.cbegin(), i.second.cend(), 0) << std::endl;