#include "lazy_value.h"
#include "gtest/gtest.h"
#include <string>

TEST(Basic, UseExample)
{
    const std::string big_string = "Giant amounts of memory";

    LazyValue<std::string> lazy_string([&big_string] { return big_string; });

    EXPECT_EQ(true, !lazy_string.HasValue());
    EXPECT_EQ(lazy_string.Get(), big_string);
    EXPECT_EQ(lazy_string.Get(), big_string);
}

TEST(Basic, TestInitializerIsntCalled)
{
    bool called = false;

    LazyValue<int> lazy_int([&called] { called = true; return 0; });
    EXPECT_EQ(true, !called);
}