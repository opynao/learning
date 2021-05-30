#include "reading_manager.h"

void ReadingManager::Read(const int user_id, const int page_count)
{
    int pageCountPrevious = user_page_counts_[user_id];
    user_page_counts_[user_id] = page_count;
    if (pageCountPrevious)
    {
        auto it = sortedInfoByPages.find({user_id, pageCountPrevious});
        if (it != sortedInfoByPages.cend())
        {
            auto nh = sortedInfoByPages.extract(it);
            nh.value().page_count = page_count;
            sortedInfoByPages.insert(std::move(nh));
        }
        else
            sortedInfoByPages.insert({user_id, page_count});
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
