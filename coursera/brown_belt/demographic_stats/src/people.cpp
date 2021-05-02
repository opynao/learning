#include "people.h"
#include <iterator>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <set>

PeopleStats::PeopleStats(const peopleStats_t &peopleByAge)
    : peopleSortByAge_{std::move(peopleByAge)}
{
    for (auto it = peopleSortByAge_.begin(); it != peopleSortByAge_.end(); ++it)
    {
        income_.emplace(it->income);
        it->is_male ? male_.emplace(it->name) : female_.emplace(it->name);
    }

    incomeSum_.assign(income_.size(), 0);

    mostPopularFemaleName_ = GetName(female_);
    mostPopularMaleName_ = GetName(male_);

    cache_->middleAge_ = peopleSortByAge_.rbegin()->age / 2;
    cache_->itMiddle_ = peopleSortByAge_.lower_bound(Person(cache_->middleAge_));
    cache_->middleNumberOfPeople_ = std::distance(cache_->itMiddle_, std::end(peopleSortByAge_));

}

size_t PeopleStats::GetAdultPeopleOlderThanAge(const size_t adult_age) const
{
    auto it = peopleSortByAge_.lower_bound(Person(adult_age));
    if (adult_age < cache_->middleAge_ && adult_age > cache_->middleAge_ / 2)
    {
        size_t diff = std::distance(it, cache_->itMiddle_);
        return (cache_->middleNumberOfPeople_ + diff);
    }
    else if (adult_age < cache_->middleAge_ && adult_age < cache_->middleAge_ / 2)
    {
        size_t diff = std::distance(peopleSortByAge_.begin(), it);
        return (peopleSortByAge_.size() - diff);
    }
    else if (adult_age > cache_->middleAge_ && adult_age < 3 * cache_->middleAge_ / 2)
    {
        size_t diff = std::distance(cache_->itMiddle_, it);
        return (cache_->middleNumberOfPeople_ - diff);
    }
    else
    {
        size_t diff = std::distance(it, peopleSortByAge_.end());
        return diff;
    }
}

size_t PeopleStats::GetPeopleWithTotalIncome(const size_t count) const
{
    auto &sum = incomeSum_[count];
    if (sum)
        return sum;
    const auto itEnd = std::next(incomeSum_.begin(), count);
    auto itFind = std::find_if_not(itEnd, incomeSum_.end(), [](auto sum) { return !sum; });
    if (itFind == incomeSum_.end())
        sum = std::accumulate(std::next(income_.begin(), incomeSum_.size() - count), income_.end(), 0);
    else
        sum = *itFind - std::accumulate(itEnd, itFind, 0);
    return sum;
}

std::optional<std::string> PeopleStats::GetMostPopularName(const char gender) const
{
    return (gender == 'M' ? mostPopularMaleName_ : mostPopularFemaleName_);
}

std::optional<std::string> PeopleStats::GetName(const std::multiset<std::string> &s) const
{
    if (s.empty())
        return {};

    int maxFreq{0};
    int freq{1};
    auto itMax = s.begin();
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        if (*it == *std::next(it))
        {
            freq++;
            if (freq > maxFreq)
            {
                maxFreq = freq;
                itMax = it;
            }
        }
        else
            freq = 1;
    }
    return *itMax;
}