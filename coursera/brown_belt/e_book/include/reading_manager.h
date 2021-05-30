#pragma once
#include "utils.h"
#include <vector>
#include <set>
#include <array>

struct UserInfo
{
    int user_number;
    int page_count;
    bool operator<(const UserInfo &userInfo) const
    {
        return page_count < userInfo.page_count;
    }
    bool operator==(const UserInfo &userInfo) const
    {
        return page_count == userInfo.page_count;
    }
};

class ReadingManager
{
public:
    void Read(const int user_id, const int page_count);

    double Cheer(const int user_id) const;

private:
    static const int MAX_USER_COUNT_ = 100'000;

    std::array<int, MAX_USER_COUNT_> user_page_counts_;
    std::multiset<UserInfo> sortedInfoByPages;
};
