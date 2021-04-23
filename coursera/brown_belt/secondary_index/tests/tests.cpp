#include "gtest/gtest.h"
#include "database.h"

TEST(Basic, RangeBoundaries)
{
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record &) {
        ++count;
        return true;
    });

    EXPECT_EQ(2, count);
}

TEST(Basic, SameUser)
{
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record &) {
        ++count;
        return true;
    });

    EXPECT_EQ(2, count);
}

TEST(Basic, Replacement)
{
    const std::string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});
    auto record = db.GetById("id");
    EXPECT_NE(record, nullptr);
    EXPECT_EQ(final_body, record->title);
}