#include "gtest/gtest.h"
#include "logger_class.h"

#include <sstream>
// logger.Log( ( l.LogFile() ? (l.LogLine() ? (l.PrintFileName() + ":" + l.PrintLine() + " " + message + "\n") : (l.PrintFileName() +" " + message + "\n")  )  
//      : (l.LogLine() ? ("Line " + l.PrintLine() + " " + message + "\n") : (message + "\n") )


TEST( TestLog, Correct_Output )
{
/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
 * и наш тест начинает падать. Это неудобно.
 *
 * Чтобы этого избежать, мы используем специальный макрос #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
 * переопределить номер строки, а также имя файла. Благодаря ему, номера
 * строк внутри функции TestLog будут фиксированы независимо от того, какой
 * код мы добавляем перед ней*/
#line 1 "logger.cpp"

  std::ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");
 
  std::string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  EXPECT_EQ(logs.str(), expected);
}


