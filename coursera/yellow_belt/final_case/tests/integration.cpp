#include "database.h"
#include "date.h"
#include "parse_date_event.h"
#include "do_find_do_remove.h"
#include "gtest/gtest.h"

#include <vector>
#include <string>
#include <utility>
#include <sstream>


class IntegrationTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
	}
	Database db;
	std::ostringstream oss;
};


TEST_F( IntegrationTest, Test1 )
{
    db.Add({2019, 12, 1}, "a");
    db.Add({2019, 12, 1}, "b");
    db.Add({2019, 12, 2}, "c c");
    db.Add({2019, 12, 2}, "d");
    db.Add({2019, 12, 3}, "e");
    db.Add({2019, 12, 3}, "f");
    db.Print(oss);
    EXPECT_EQ("2019-12-01 a\n2019-12-01 b\n2019-12-02 c c\n2019-12-02 d\n2019-12-03 e\n2019-12-03 f\n", oss.str());
    EXPECT_EQ(1, DoRemove(db, R"(event == "c" OR event == "d")" ));
    EXPECT_EQ(1, DoRemove(db, R"(event == "e" AND event != "a")"));
    db.Add({2019, 11, 30}, "a");
    EXPECT_EQ("2019-12-03 f\n1", DoFind(db, R"(date >= 2019-12-3)"));
/*    AssertEqual(Entry({2019, 12, 3}, "f"), db.Last({2019, 12, 4}), " My test 6");

    try
    {
        db.Last({2019, 11, 3});    
    }
    catch(invalid_argument&)
    {
        cerr << "Тест на No entries OK" << endl;
    }*/
}


