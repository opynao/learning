#pragma once
#include <vector>
#include <string>

std::vector<std::string_view> SplitIntoWords(std::string_view line);

size_t FindWordBeginning(std::string_view line, size_t pos);