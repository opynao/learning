#pragma once

#include <mutex>
#include <unordered_map>
#include <vector>

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap
{
public:
    using MapType = std::unordered_map<K, V, Hash>;

    struct WriteAccess
    {
        std::lock_guard<std::mutex> m;
        V &ref_to_value;
    };

    struct ReadAccess
    {
        std::lock_guard<std::mutex> m;
        const V &ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count)
        : buckets_(bucket_count)
    {
    }

    WriteAccess operator[](const K &key)
    {
        auto &bucket = buckets_[get_bucket_number(key)];
        return {std::lock_guard<std::mutex>(bucket.first), bucket.second[key]};
    }
    ReadAccess At(const K &key) const
    {
        auto &bucket = buckets_[get_bucket_number(key)];
        return {std::lock_guard<std::mutex>(bucket.first), bucket.second.at(key)};
    }

    bool Has(const K &key) const
    {
        return buckets_[get_bucket_number(key)].second.count(key);
    }

    MapType BuildOrdinaryMap() const
    {
        MapType result;
        for (auto &map : buckets_)
        {
            std::lock_guard<std::mutex> guard(map.first);
            result.insert(map.second.begin(), map.second.end());
        }
        return result;
    }

private:
    size_t get_bucket_number(const K &key) const
    {
        return hasher(key) % buckets_.size();
    }

private:
    Hash hasher;
    mutable std::vector<std::pair<std::mutex, std::unordered_map<K, V, Hash>>> buckets_;
};
