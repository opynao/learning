#pragma once
#include <algorithm>
#include <future>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <mutex>
#include <utility>

using namespace std;

template <typename Key, typename Value>
class ConcurrentMap
{
private:
  struct bucket_type
  {
    std::lock_guard<std::mutex> mutex;
    Value &ref_to_value;
  };

  /*
  private:
    bucket_iterator find_entry_for(const Key &key) const
    {
      return std::find_if(data.begin(), data.end(),
                          [&](const bucket_values) { return item.first == key; });
    }

  public:
    bucket_reference &value_for(const Key &key, const Value &default_value = Value()) const
    {
      std::shared_lock<std::shared_mutex> lock(mutex);
      const bucket_iterator found_entry = find_entry_for(key);
      return (found_entry == data.end()) ? default_value : found_entry->second;
    }
      void add_or_update_mapping(const Key &key, const Value &value)
    {
      std::unique_lock<std::shared_mutex> lock(mutex);
      const bucket_iterator found_entry = find_entry_for(key);
      if (found_entry == data.end())
        data.push_back(bucket_value(key, value));
      else
        found_entry->second = value;
    }
 };*/

private:
  std::vector<std::pair<std::mutex, std::map<Key, Value>>> buckets;

  size_t get_bucket_number(const Key &key) const
  {
    return key % buckets.size();
  }

public:
  static_assert(is_integral_v<Key>, "ConcurrentMap supports only integer keys");

  explicit ConcurrentMap(size_t bucket_count)
      : buckets(bucket_count)
  {
  }

  bucket_type operator[](const Key &key)
  {
    auto &bucket = buckets[get_bucket_number(key)];
    return {std::lock_guard<std::mutex>(bucket.first), bucket.second[key]};
  }

  std::map<Key, Value> BuildOrdinaryMap()
  {
    std::map<Key, Value> result;

    for (auto &map : buckets)
    {
      std::lock_guard<std::mutex> guard(map.first);
      result.insert(map.second.begin(), map.second.end());
    }
    return result;
  }
};
