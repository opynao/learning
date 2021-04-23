#include <string>
#include <map>
#include <set>
#include <iostream>
#include <unordered_map>

#define LOGF std::cerr << __FUNCTION__ << " : " << __LINE__ << std::endl
#define PR(x) std::cerr << #x << " = " << x << std::endl

struct Record
{
    std::string id;
    std::string title;
    std::string user;
    int timestamp;
    int karma;
};

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

struct Data
{
    using IteratorInt_t = std::multimap<int, Record *>::iterator;
    using IteratorString_t = std::multimap<std::string, Record *>::iterator;

    Data(const IteratorInt_t itTempStamp,
         const IteratorInt_t itKarma,
         const IteratorString_t itUser,
         const Record record)
        : itTimeStamp_{itTempStamp}, itKarma_{itKarma}, itUser_{itUser}, record_{record}
    {
    }
    IteratorInt_t itTimeStamp_{};
    IteratorInt_t itKarma_{};
    IteratorString_t itUser_{};
    Record record_{};
};

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
bool Database::Put(const Record &record)
{
    auto [it, inserted] = data_.emplace(record.id, Data({}, {}, {}, record));
    if (!inserted)
        return false;
    auto &data = it->second;
    Record *ptr = &data.record_;
    data.itTimeStamp_ = timeStamp_.Insert(record.timestamp, ptr);
    data.itKarma_ = karma_.Insert(record.karma, ptr);
    data.itUser_ = user_.Insert(record.user, ptr);
    return true;
}

const Record *Database::GetById(const std::string &id) const
{
    auto it = data_.find(id);
    return it == data_.cend() ? nullptr : &(it->second.record_);
}

bool Database::Erase(const std::string &id)
{
    auto it = data_.find(id);
    if (it == data_.cend())
        return false;
    else
    {
        auto &data = it->second;

        timeStamp_.Erase(data.itTimeStamp_);
        karma_.Erase(data.itKarma_);
        user_.Erase(data.itUser_);
        data_.erase(it);
        return true;
    }
}
int main()
{
    return 0;
}