#pragma once

#include "record.h"
#include "data.h"
#include "index.h"

#include <iostream>
#include <map>
#include <unordered_map>

#define LOGF std::cerr << __FUNCTION__ << " : " << __LINE__ << std::endl
#define PR(x) std::cerr << #x << " = " << x << std::endl

class Database
{
public:
    using id_t = std::string;

public:
    bool Put(const Record &record);
    const Record *GetById(const std::string &id) const;
    bool Erase(const std::string &id);

public:
    template <typename Callback>
    void RangeBy(int low, int high, Callback callback, Index<int> &index) const
    {
        auto itLow = index.Lower_Bound(low);
        auto itHigh = index.Upper_Bound(high);
        for (auto it = itLow; it != itHigh; ++it)
        {
            if (!callback(*it->second))
                break;
        }
    }
    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const
    {
        RangeBy(low, high, callback, timeStamp_);
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const
    {
        RangeBy(low, high, callback, karma_);
    }

    template <typename Callback>
    void AllByUser(const std::string &user, Callback callback) const
    {
        auto [itLow, itHigh] = user_.FindRange(user);
        for (auto it = itLow; it != itHigh; ++it)
        {
            if (!callback(*it->second))
                break;
        }
    }

private:
    std::unordered_map<id_t, Data> data_;
    mutable Index<int> timeStamp_;
    mutable Index<int> karma_;
    mutable Index<std::string> user_;
};
