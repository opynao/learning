#pragma once
#include <iterator>
#include <algorithm>

template <typename Iterator>
class IteratorRange
{
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin), last(end)
    {
    }

    Iterator begin() const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }

private:
    Iterator first, last;
};

template <typename Collection>
auto Head(Collection &v, size_t top)
{
    return IteratorRange{v.begin(), std::next(v.begin(), std::min(top, v.size()))};
}