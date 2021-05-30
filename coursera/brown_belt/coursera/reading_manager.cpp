#include <iostream>
#include <string>
#include <iomanip>
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

void ReadingManager::Read(const int user_id, const int page_count)
{
    int pageCountPrevious = user_page_counts_[user_id];
    user_page_counts_[user_id] = page_count;
    if (pageCountPrevious)
    {
        auto it = sortedInfoByPages.find({user_id, pageCountPrevious});
        auto nh = sortedInfoByPages.extract(it);
        nh.value().page_count = page_count;
        sortedInfoByPages.insert(std::move(nh));
    }
    else
        sortedInfoByPages.insert({user_id, page_count});
}

double ReadingManager::Cheer(const int user_id) const
{
    const int page_count = user_page_counts_[user_id];
    const int sortedInfoByPagesSize = sortedInfoByPages.size();
    if (page_count == 0)
        return 0;

    if (sortedInfoByPagesSize == 1)
        return 1;

    auto it = sortedInfoByPages.find({user_id, page_count});

    return (static_cast<double>(std::distance(sortedInfoByPages.begin(), it)) / (sortedInfoByPagesSize - 1));
}

class Parser
{
public:
    Parser(std::istream &is, std::ostream &os);

private:
    void ParseQuery(ReadingManager &manager);
    std::istream &m_is;
    std::ostream &m_os;
};

Parser::Parser(std::istream &is, std::ostream &os)
    : m_is{is}, m_os{os}
{
    ReadingManager manager;

    int query_count;
    m_is >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
        ParseQuery(manager);
}

void Parser::ParseQuery(ReadingManager &manager)
{
    std::string query_type;
    m_is >> query_type;

    int user_id;
    m_is >> user_id;

    if (query_type == "READ")
    {
        int page_count;
        m_is >> page_count;
        manager.Read(user_id, page_count);
    }

    else if (query_type == "CHEER")
        m_os << std::setprecision(6) << manager.Cheer(user_id) << "\n";
}

int main()
{
    Parser parser(std::cin, std::cout);
    return 0;
}