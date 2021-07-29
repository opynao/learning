#pragma once
#include <optional>
#include <string_view>
#include <vector>
#include <utility>

std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view s, std::string_view delimiter = " ");

std::vector<std::string_view> Split(std::string_view s, std::string_view delimiter = " ");