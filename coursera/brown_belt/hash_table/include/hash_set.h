//#pragma once

#include <forward_list>
#include <algorithm>
#include <vector>
#include <iostream>

#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl
#define PR(x) std::cerr << #x << " = " << x << std::endl

//using namespace std;

template <typename Type, typename Hasher>
class HashSet
{
public:
    using BucketList = std::forward_list<Type>;

public:
    explicit HashSet(size_t num_buckets, const Hasher &hasher = {})
        : buckets_(num_buckets), hasher_{hasher}
    {
    }

    void Add(const Type &value)
    {
        BucketList &bucket = buckets_[GetHashNumber(value)];
        if (!Has(value))
            bucket.push_front(value);
    }

    bool Has(const Type &value) const
    {
        const auto &bucket = GetBucket(value);
        return std::find(bucket.cbegin(), bucket.cend(), value) != GetBucket(value).cend();
    }

    void Erase(const Type &value)
    {
        buckets_[GetHashNumber(value)].remove(value);
    }

    const BucketList &GetBucket(const Type &value) const
    {
        return buckets_[GetHashNumber(value)];
    }

private:
    size_t GetHashNumber(const Type &value) const
    {
        return hasher_(value) % buckets_.size();
    }

private:
    std::vector<BucketList> buckets_;
    Hasher hasher_;
};

int main()
{
    return 0;
}