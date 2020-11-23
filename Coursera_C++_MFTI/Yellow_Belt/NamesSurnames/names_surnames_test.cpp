#include "names_surnames.h"
#include "gtest/gtest.h"


class PersonTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	Person person;
};

TEST_F( PersonTest, Person_ChangeLastAndFirstName_GetFullNameReturnsLastAndFirstName)
{
	person.ChangeLastName(1996,"Gorbachyova");
	person.ChangeFirstName(1996,"Viktoria");
	EXPECT_EQ( person.GetFullName(1996), "Viktoria Gorbachyova" );
}

TEST_F( PersonTest, Person_ChangeLastName_GetFullNameReturnsLastNameWithUnknownFirstName)
{
	person.ChangeLastName(1996,"Gorbachyova");
	EXPECT_EQ( person.GetFullName(1996), "Gorbachyova with unknown first name" );
}

TEST_F( PersonTest, Person_ChangeFirstName_GetFullNameReturnsFirstNameWithUnknownLastName)
{
	person.ChangeFirstName(1996,"Viktoria");
	EXPECT_EQ( person.GetFullName(1996), "Viktoria with unknown last name" );
}

TEST_F( PersonTest, Person_IsIncognito)
{
	person.ChangeFirstName(1996,"Viktoria");
	EXPECT_EQ( person.GetFullName(1992), "Incognito" );
}

int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
