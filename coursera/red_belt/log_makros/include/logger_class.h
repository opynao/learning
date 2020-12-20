#pragma once
#include <iostream>
#include <string>

#define LOG(logger, message) logger.Log(message, __FILE__, __LINE__)


class Logger 
{
public:
  explicit Logger(std::ostream& output_stream) 
    : os(output_stream)
  {} 
  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file = value; }

  void Log(const std::string& message) { os << message; }
  bool LogLine() const { return log_line; }
  bool LogFile() const { return log_file; }
  void Log(const std::string& message, const std::string& fileName, const size_t lineNumber)
  {
    if( !log_line && !log_file )
      os << message << "\n";
    if( log_file && !log_line )
      os << fileName << " " << message << "\n";
    if( log_file && log_line )
      os << fileName << ":" << lineNumber << " " << message << "\n";
    if( !log_file && log_line )
      os << "Line " << lineNumber << " " << message << "\n";
  }

private:
  std::ostream& os;
  bool log_line = false;
  bool log_file = false;
};
