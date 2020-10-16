#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

class TemperatureCalendar {};

class TemperatureCalendarTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE( TemperatureCalendarTest );
	CPPUNIT_TEST( TestConstructor );
  	CPPUNIT_TEST_SUITE_END();
public:
	void TestConstructor()
  	{
		const auto ptr = std::make_shared<TemperatureCalendar>();
		CPPUNIT_ASSERT( nullptr != ptr);
  	}
 	void setUp() {}
  	void tearDown() {}

};

CPPUNIT_TEST_SUITE_REGISTRATION( TemperatureCalendarTest );
int main(int argc, char* argv[])
{
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );
  runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(), std::cerr ) );
  bool wasSucessful = runner.run();
  return wasSucessful ? 0 : 1;
} 
