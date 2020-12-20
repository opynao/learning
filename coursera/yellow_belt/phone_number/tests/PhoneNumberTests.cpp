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
#include <gtest/gtest.h>
#include "../phone_number.h"

TEST( PhoneNumberTest, Correct_Input )
{
	PhoneNumber pn("+7-495-111-22-23");
	EXPECT_EQ( pn.GetCountryCode(), "7" );
	EXPECT_EQ( pn.GetCityCode(), "495" );
	EXPECT_EQ( pn.GetLocalNumber(), "111-22-23" );
}


int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
