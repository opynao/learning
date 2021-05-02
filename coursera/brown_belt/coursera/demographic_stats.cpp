#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <istream>
#include <functional>
#include <numeric>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <set>

struct Person
{
    Person() = default;
    Person(int age_)
        : age{age_}
    {
    }
    std::string name;
    int age;
    int income;
    bool is_male;
    bool operator<(const Person &person) const
    {
        return age < person.age;
    }
};

std::multiset<Person> ReadPeople(std::istream &input)
{
    int count;
    input >> count;

    std::multiset<Person> result;
    for (int i = 0; i != count; ++i)
    {
        Person p;
        char gender;
        input >> p.name >> p.age >> p.income >> gender;
        p.is_male = gender == 'M';
        result.insert(std::move(p));
    }

    return result;
}

class PeopleStats
{
public:
    PeopleStats() = default;
    explicit PeopleStats(const std::multiset<Person> &people);
    size_t GetAdultPeopleOlderThanAge(const size_t adult_age) const;
    size_t GetPeopleWithTotalIncome(const size_t count) const;
    std::optional<std::string> GetMostPopularName(const char gender) const;
    std::optional<std::string> GetName(const std::multiset<std::string> &s) const;

private:
    std::multiset<Person> peopleSortByAge_;
    std::multiset<int> income_;
    std::multiset<std::string> male_;
    std::multiset<std::string> female_;

    mutable std::vector<size_t> incomeSum_;
    std::optional<std::string> mostPopularMaleName_;
    std::optional<std::string> mostPopularFemaleName_;

    struct Cache
    {
        size_t middleAge_;
        size_t middleNumberOfPeople_;
        std::multiset<Person>::iterator itMiddle_;
    };
    std::optional<Cache> cache_;
};

PeopleStats::PeopleStats(const std::multiset<Person> &peopleByAge)
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

class CommandHandler
{
public:
    typedef void (CommandHandler::*pFunc)(const PeopleStats &people, std::istream &is, std::ostream &os) const;
    using functionCall_t = std::unordered_map<std::string, pFunc>;

public:
    CommandHandler(std::istream &is, std::ostream &os);
    void CommandAge(const PeopleStats &people, std::istream &is, std::ostream &os) const;
    void CommandWealthy(const PeopleStats &people, std::istream &is, std::ostream &os) const;
    void CommandPopularName(const PeopleStats &people, std::istream &is, std::ostream &os) const;

private:
    functionCall_t commands{
        {"AGE", &CommandHandler::CommandAge},
        {"WEALTHY", &CommandHandler::CommandWealthy},
        {"POPULAR_NAME", &CommandHandler::CommandPopularName}};
};

CommandHandler::CommandHandler(std::istream &is, std::ostream &os)
{
    const PeopleStats people(ReadPeople(is));
    for (std::string command; is >> command;)
    {
        auto itCommand = commands.find(command);
        if (itCommand != commands.cend())
            (this->*itCommand->second)(people, is, os);
    }
}

void CommandHandler::CommandAge(const PeopleStats &people, std::istream &is, std::ostream &os) const
{
    size_t adult_age;
    is >> adult_age;
    os << "There are " << people.GetAdultPeopleOlderThanAge(adult_age);
    os << " adult people for maturity age " << adult_age << '\n';
}

void CommandHandler::CommandWealthy(const PeopleStats &people, std::istream &is, std::ostream &os) const
{
    size_t count;
    is >> count;
    os << "Top-" << count << " people have total income ";
    os << people.GetPeopleWithTotalIncome(count) << '\n';
}

void CommandHandler::CommandPopularName(const PeopleStats &people, std::istream &is, std::ostream &os) const
{
    char gender;
    is >> gender;
    auto name = people.GetMostPopularName(gender);
    if (!name)
        os << "No people of gender " << gender << '\n';
    else
        os << "Most popular name among people of gender " << gender << " is " << name.value() << '\n';
}

int main()
{
    CommandHandler cmd(std::cin, std::cout);
    return 0;
}