#pragma once
#include <set>
#include <map>
#include <unordered_map>

#include "record.h"
#include "data.h"

template <typename T>
struct Index
{
    using Iterator_t = typename std::multimap<T, Record *>::iterator;

    std::multimap<T, Record *> m_;
    Iterator_t Insert(T value, Record *record)
    {
        return m_.emplace(value, record);
    }
    void Erase(Iterator_t it)
    {
        m_.erase(it);
    }
    Iterator_t Lower_Bound(const T &value)
    {
        return m_.lower_bound(value);
    }
    Iterator_t Upper_Bound(const T &value)
    {
        return m_.upper_bound(value);
    }
    std::pair<Iterator_t, Iterator_t> FindRange(const T &value)
    {
        return m_.equal_range(value);
    }
};