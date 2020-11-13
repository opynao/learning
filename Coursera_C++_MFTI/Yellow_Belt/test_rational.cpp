#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>
#include <string>
#include <iomanip>
#include <cassert>

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

/*
class Rational {
public:
	Rational();
	Rational(int, int); 
	int Numerator() const;
	int Denominator() const;
private:
	void Reduct();
	int m_numerator {};
	int m_denominator {};
};

Rational::Rational()
	: m_numerator {0}
	, m_denominator {1}
{
}

Rational::Rational(int numerator, int denominator)
	: m_numerator {numerator}
	, m_denominator {denominator}
{
	Reduct();
}

int Rational::Numerator() const
{
	return m_numerator;
}

int Rational::Denominator() const
{
	return m_denominator;
}

void Rational::Reduct()
{
	int nod = std::gcd(m_numerator,m_denominator);
	m_numerator = m_numerator/nod;
	m_denominator = m_denominator/nod;
	if(m_denominator < 0)
	{
		m_denominator = -m_denominator;
		m_numerator = -m_numerator;
	}	
}
*/
void testDefaultConstruct()
{
	Rational rational;
	AssertEqual( rational.Numerator(), 0 );
	AssertEqual( rational.Denominator(), 1);
}

void testConstructReduction()
{
	Rational rational(4,6);
	AssertEqual( rational.Numerator(), 2 );
	AssertEqual( rational.Denominator(), 3);
}

void testConstructNegativeFraction()
{
	Rational rational(4,-6);
	AssertEqual( rational.Numerator(), -2 );
	AssertEqual( rational.Denominator(), 3 );
}

void testConstructWithNegativeArgs()
{
	Rational rational(-4,-6);
	AssertEqual( rational.Numerator(), 2 );
	AssertEqual( rational.Denominator(), 3 );
}

void testConstructWithNullNumerator()
{
	Rational rational(0,-6);
	AssertEqual( rational.Numerator(), 0 );
	AssertEqual( rational.Denominator(), 1 );
}

void testAll()
{
	TestRunner runner;
	runner.RunTest( testDefaultConstruct, "testDefaultConstruct" );
	runner.RunTest( testConstructReduction, "testConstructReduction" );
	runner.RunTest( testConstructNegativeFraction, "testConstructNegativeFraction" );
	runner.RunTest( testConstructWithNegativeArgs, "testConstructWithNegativeArgs" );
	runner.RunTest( testConstructWithNullNumerator, "testConstructWithNullNumerator" );


}

int main() 
{
	testAll();
	return 0;
}
