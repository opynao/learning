#pragma once
#include "split.h"
#include "range.h"

#include <string>
#include <string_view>
#include <vector>
#include <iostream>

class Domain
{
public:
    explicit Domain(std::string_view text)
    {
        std::vector<std::string_view> parts = Split(text, ".");
        parts_reversed_.assign(std::rbegin(parts), std::rend(parts));
    }

    size_t GetPartCount() const
    {
        return parts_reversed_.size();
    }

    auto GetParts() const
    {
        return Range(std::rbegin(parts_reversed_), std::rend(parts_reversed_));
    }
    auto GetReversedParts() const
    {
        return Range(std::begin(parts_reversed_), std::end(parts_reversed_));
    }

    bool operator==(const Domain &other) const
    {
        return parts_reversed_ == other.parts_reversed_;
    }

private:
    std::vector<std::string> parts_reversed_;
};

std::ostream &operator<<(std::ostream &stream, const Domain &domain);