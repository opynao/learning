#pragma once
#include "entry.h"
#include "synchronized.h"

#include <vector>
#include <map>
#include <string>
#include <deque>
#include <set>
#include <cstdint>

class InvertedIndex
{
public:
    using docid_t = uint16_t;
    // using word_t = std::string_view;
    using word_t = std::string;

    using wordOccurence_t = uint16_t;
    using wordInfo_t = std::vector<wordOccurence_t>;
    //   using index_t = std::map<std::string_view, wordInfo_t>;
    using index_t = std::map<std::string, wordInfo_t>;
    using docs_t = std::deque<std::string>;

public:
    void Add(std::string &&document, docid_t docid);
    const wordInfo_t &Lookup(const word_t &word) const;

public:
    void AddWordOccurence(const word_t &word, const docid_t docid);

private:
    index_t index{};
    docs_t docs{};
};
