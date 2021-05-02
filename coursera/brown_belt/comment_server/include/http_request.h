#pragma once

#include <string>
#include <utility>
#include <map>

struct HttpRequest
{
    std::string method{};
    std::string path{};
    std::string body{};
    std::map<std::string, std::string> get_params{};
};

struct LastCommentInfo
{
    size_t user_id;
    size_t consecutive_count;
};

std::pair<std::string, std::string> SplitBy(const std::string &what, const std::string &by);

template <typename T>
T FromString(const std::string &s);

std::pair<size_t, std::string> ParseIdAndContent(const std::string &body);