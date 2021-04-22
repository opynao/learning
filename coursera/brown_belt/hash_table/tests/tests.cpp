#include "hash_set.h"
#include "gtest/gtest.h"

#include <iterator>

struct IntHasher
{
    size_t operator()(int value) const
    {
        // Это реальная хеш-функция из libc++, libstdc++.
        // Чтобы она работала хорошо, std::unordered_map
        // использует простые числа для числа бакетов
        return value;
    }
};

struct TestValue
{
    int value;

    bool operator==(TestValue other) const
    {
        return value / 2 == other.value / 2;
    }
};

struct TestValueHasher
{
    size_t operator()(TestValue value) const
    {
        return value.value / 2;
    }
};

TEST(Basic, Smoke)
{
    HashSet<int, IntHasher> hash_set(2);
    hash_set.Add(3);
    hash_set.Add(4);

    EXPECT_EQ(hash_set.Has(3), true);
    EXPECT_EQ(hash_set.Has(4), true);
    EXPECT_EQ(!hash_set.Has(5), true);

    hash_set.Erase(3);

    EXPECT_EQ(!hash_set.Has(3), true);
    EXPECT_EQ(hash_set.Has(4), true);
    EXPECT_EQ(!hash_set.Has(5), true);

    hash_set.Add(3);
    hash_set.Add(5);

    EXPECT_EQ(hash_set.Has(3), true);
    EXPECT_EQ(hash_set.Has(4), true);
    EXPECT_EQ(hash_set.Has(5), true);
}

TEST(Basic, Empty)
{
    HashSet<int, IntHasher> hash_set(10);
    for (int value = 0; value < 10000; ++value)
    {
        EXPECT_EQ(!hash_set.Has(value), true);
    }
}

TEST(Basic, Idempotency)
{
    HashSet<int, IntHasher> hash_set(10);
    hash_set.Add(5);
    EXPECT_EQ(hash_set.Has(5), true);
    hash_set.Add(5);
    EXPECT_EQ(hash_set.Has(5), true);
    hash_set.Erase(5);
    EXPECT_EQ(!hash_set.Has(5), true);
    hash_set.Erase(5);
    EXPECT_EQ(!hash_set.Has(5), true);
}

TEST(Basic, Equivalence)
{
    HashSet<TestValue, TestValueHasher> hash_set(10);
    hash_set.Add(TestValue{2});
    hash_set.Add(TestValue{3});

    EXPECT_EQ(hash_set.Has(TestValue{2}), true);
    EXPECT_EQ(hash_set.Has(TestValue{3}), true);

    const auto &bucket = hash_set.GetBucket(TestValue{2});
    const auto &three_bucket = hash_set.GetBucket(TestValue{3});
    EXPECT_EQ(&bucket, &three_bucket);
    EXPECT_EQ(1, std::distance(begin(bucket), end(bucket)));
    EXPECT_EQ(2, bucket.front().value);
}