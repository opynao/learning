#include "gtest/gtest.h"
#include "booking_manager.h"
#include "parser.h"
#include "profile.h"

#include <sstream>

class BookingManagerBasicTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        bm.Book(10, "FourSeasons", 1, 2);
        bm.Book(100, "Michell", 2, 3);
    }
    BookingManager bm;
};

TEST_F(BookingManagerBasicTest, Book)
{
    EXPECT_EQ(bm.GetStorageSize(), 2);
}

TEST_F(BookingManagerBasicTest, Clients)
{
    EXPECT_EQ(bm.Clients("FourSeasons"), 1);
    EXPECT_EQ(bm.Clients("Michell"), 1);

    bm.Book(110, "FourSeasons", 3, 5);
    EXPECT_EQ(bm.Clients("FourSeasons"), 2);

    bm.Book(90000, "AsiaBeach", 3, 5);
    EXPECT_EQ(bm.Clients("FourSeasons"), 0);
}

TEST_F(BookingManagerBasicTest, Rooms)
{
    EXPECT_EQ(bm.Rooms("FourSeasons"), 2);
    EXPECT_EQ(bm.Rooms("Michell"), 3);

    bm.Book(110, "FourSeasons", 3, 5);
    EXPECT_EQ(bm.Rooms("FourSeasons"), 7);

    bm.Book(90000, "AsiaBeach", 3, 5);
    EXPECT_EQ(bm.Clients("FourSeasons"), 0);

    bm.Book(90001, "FourSeasons", 3, 5);
    EXPECT_EQ(bm.Rooms("FourSeasons"), 5);
}

TEST_F(BookingManagerBasicTest, Clients_noHotelInStorage)
{
    EXPECT_EQ(bm.Clients("AsiaBeach"), 0);
}

TEST_F(BookingManagerBasicTest, Rooms_noHotelInStorage)
{
    EXPECT_EQ(bm.Rooms("AsiaBeach"), 0);
}

TEST(BasicTest, Test)
{
    std::istringstream is("11\n \
     CLIENTS Marriott\n \
     ROOMS Marriott\n \
     BOOK 10 FourSeasons 1 2\n \
     BOOK 10 Marriott 1 1\n \
     BOOK 86409 FourSeasons 2 1\n \
     CLIENTS FourSeasons\n \
     ROOMS FourSeasons\n \
     CLIENTS Marriott\n \
     BOOK 86410 Marriott 2 10\n \
     ROOMS FourSeasons\nROOMS Marriott");
    std::ostringstream os;
    Parser parser(is, os);
    EXPECT_EQ(os.str(), "0\n0\n2\n3\n1\n1\n10\n");
}

TEST(BasicTest, Test1)
{
    std::istringstream is("12\n \
     ROOMS a\n \
     CLIENTS a\n \
     BOOK -100000 a 100000 1000\n \
     BOOK -100000 a 100003 1000\n \
     BOOK -100000 b 100002 1000\n \
     ROOMS a\n \
     CLIENTS a\n \
     BOOK -10000 a 100002 1000\n \
     ROOMS a\n \
     CLIENTS a\n \
     ROOMS b\n \
     CLIENTS b");
    std::ostringstream os;
    Parser parser(is, os);
    EXPECT_EQ(os.str(), "0\n0\n2000\n2\n1000\n1\n0\n0\n");
}

TEST(Clients, SomeSameClients)
{
    BookingManager bm;
    bm.Book(110, "FourSeasons", 3, 5);
    bm.Book(110, "FourSeasons", 2, 5);
    bm.Book(110, "FourSeasons", 1, 5);
    bm.Book(111, "FourSeasons", 3, 5);
    bm.Book(111, "FourSeasons", 2, 5);
    EXPECT_EQ(bm.Clients("FourSeasons"), 3);
}

TEST(BasicTest, Test2)
{
    BookingManager manager;

    // Test empty Bookings
    EXPECT_EQ(manager.Clients("mariott"), 0);
    EXPECT_EQ(manager.Rooms("mariott"), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    EXPECT_EQ(manager.Clients("mariott"), 4);
    EXPECT_EQ(manager.Rooms("mariott"), 13);
    EXPECT_EQ(manager.Clients("hilton"), 2);
    EXPECT_EQ(manager.Rooms("hilton"), 2);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    EXPECT_EQ(manager.Clients("mariott"), 1);
    EXPECT_EQ(manager.Rooms("mariott"), 1);
    EXPECT_EQ(manager.Clients("hilton"), 1);
    EXPECT_EQ(manager.Rooms("hilton"), 1);

    // Test no Clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    EXPECT_EQ(manager.Clients("mariott"), 2);
    EXPECT_EQ(manager.Rooms("mariott"), 2);
    EXPECT_EQ(manager.Clients("hilton"), 0);
    EXPECT_EQ(manager.Rooms("hilton"), 0);
}

TEST(BasicTest, Test3)
{
    BookingManager b;

    EXPECT_EQ(b.Rooms("a"), 0);
    EXPECT_EQ(b.Clients("a"), 0);

    EXPECT_EQ(b.Rooms("b"), 0);
    EXPECT_EQ(b.Clients("c"), 0);

    b.Book(-100000, "a", 100000, 1000);
    b.Book(-100000, "a", 100003, 1000);
    b.Book(-100000, "b", 100002, 1000);
    EXPECT_EQ(b.Rooms("a"), 2000);
    EXPECT_EQ(b.Clients("a"), 2);

    b.Book(-10000, "a", 100002, 1000);
    EXPECT_EQ(b.Rooms("a"), 1000);
    EXPECT_EQ(b.Clients("a"), 1);
    EXPECT_EQ(b.Rooms("b"), 0);
    EXPECT_EQ(b.Clients("b"), 0);
}

TEST(BasicTest, Test4)
{
    BookingManager b;

    b.Book(0, "a", 0, 1);
    b.Book(1, "a", 1, 2);
    b.Book(86400, "a", 1, 3);
    EXPECT_EQ(b.Clients("a"), 1);
    EXPECT_EQ(b.Rooms("a"), 5);
}

TEST(BasicTest, Test5)
{
    BookingManager b;

    b.Book(-86400, "a", 2, 2);
    b.Book(0, "a", 1, 5);
    EXPECT_EQ(b.Clients("a"), 1);
    EXPECT_EQ(b.Rooms("a"), 5);
}

TEST(BasicTest, Test6)
{
    BookingManager b;

    b.Book(1, "a", 11, 4);
    b.Book(50000, "a", 11, 5);
    b.Book(90000, "a", 22, 2);
    EXPECT_EQ(b.Clients("a"), 2);
    EXPECT_EQ(b.Rooms("a"), 7);
}

TEST(BasicTest, Test7)
{
    BookingManager b;

    b.Book(2147483647, "a", 1, 3);
    b.Book(2147483648, "a", 2, 11);
    b.Book(4147483648, "a", 3, 13);
    EXPECT_EQ(b.Clients("a"), 1);
    EXPECT_EQ(b.Rooms("a"), 13);
}

TEST(BasicTest, BookProfile)
{
    BookingManager bm;
    {
        LOG_DURATION("Booking");
        for (int64_t i = 0; i != 100'000; i += 10)
        {
            bm.Book(i, "a", 1, 1);
            bm.Book(i, "b", 2, 2);
        }
    }
}

TEST(BasicTest, GetClientsProfile)
{
    BookingManager bm;
    {
        LOG_DURATION("Clients");
        for (int64_t i = 0; i != 100'000; i += 10)
        {
            bm.Book(i, "a", 1, 1);
            bm.Clients("b");
            bm.Book(i, "b", 2, 2);
            bm.Clients("a");
        }
    }
}

TEST(BasicTest, GetRoomsProfile)
{
    BookingManager bm;
    {
        LOG_DURATION("Rooms");
        for (int64_t i = 0; i != 100'000; i += 10)
        {
            bm.Book(i, "a", 1, 1);
            bm.Rooms("b");
            bm.Book(i, "b", 2, 2);
            bm.Rooms("a");
        }
    }
}