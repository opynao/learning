#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cassert>
#include <iterator>
#include <utility>
#include <algorithm>


using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const std::string& str)
{
	std::string str_copy{};
        copy(str.rbegin(),str.rend(),std::back_inserter(str_copy));
	return str_copy == str;
}


void TestIsPalindrom()
{
	using vTestData_t = std::vector<std::pair<std::string,bool>>;
	vTestData_t vTestData {{"madam",true},{"gentelmen",false},{"X",true},{"",true},{" ca ac ",true},{"12321",true},{" madam",false},{"wasitacaroracatisaw",true},{" ",true},{"madaM",false},{"Level",false},{"leveL",false},{"l  e  v  e  l",true},{"lev e  l   ",false},{"  lool   ",false},{"777778",false},{"777777",true},{"abcderdcba",false},{"abcdeedcbaz",false},{"zabcdeedcba",false}};
	std::for_each(vTestData.cbegin(),vTestData.cend(),[](vTestData_t::const_reference vTestData)
			{
				AssertEqual(IsPalindrom(vTestData.first), vTestData.second);
			}
		     );
}



int main()
{
	TestRunner runner;
	runner.RunTest( TestIsPalindrom, "TestIsPalindrom" );
	return 0;
}
