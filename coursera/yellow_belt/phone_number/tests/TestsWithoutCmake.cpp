#include <cassert>
#include <iostream>
#include "phone_number.h"

  /* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

     Примеры:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - некорректный номер - не начинается на '+'
     * +7-1233 - некорректный номер - есть только код страны и города
  */

void testCorrectPhoneNumber()
{
	PhoneNumber pn("+7-495-111-22-33");
	assert(pn.GetCountryCode() == "7");
	assert(pn.GetCityCode() == "495");
	assert(pn.GetLocalNumber() == "111-22-33");
}

void testCorrectPhoneNumber2()
{
	PhoneNumber pn("+7-495-1112233");
	assert(pn.GetCountryCode() == "7");
	assert(pn.GetCityCode() == "495");
	assert(pn.GetLocalNumber() == "1112233");
}

void testCorrectPhoneNumber3()
{
	PhoneNumber pn("+323-22-460002");
	assert(pn.GetCountryCode() == "323");
	assert(pn.GetCityCode() == "22");
	assert(pn.GetLocalNumber() == "460002");
}

void testCorrectPhoneNumber4()
{
	PhoneNumber pn("+1-2-coursera-cpp");
	assert(pn.GetCountryCode() == "1");
	assert(pn.GetCityCode() == "2");
	assert(pn.GetLocalNumber() == "coursera-cpp");
}

void testInCorrectPhoneNumber_WithoutPlus()
{
	bool isException {false};
	try
	{
		PhoneNumber pn("1-2-333");
	}
	catch(...)
	{
		isException = true;	
	}
	assert(true == isException);
}

void testInCorrectPhoneNumber_WithoutLocalNumber()
{
	bool isException {false};
	try
	{
		PhoneNumber pn("+1-2");
	}
	catch(...)
	{
		isException = true;	
	}
	assert(true == isException);
}


void TestAll()
{
	testCorrectPhoneNumber();
	testCorrectPhoneNumber2();
	testCorrectPhoneNumber3();
	testCorrectPhoneNumber4();
	testInCorrectPhoneNumber_WithoutPlus();
	testInCorrectPhoneNumber_WithoutLocalNumber();
}




