#include "database.h"
#include <iostream>

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
