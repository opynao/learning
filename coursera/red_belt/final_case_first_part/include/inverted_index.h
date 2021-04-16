#pragma once
#include "entry.h"
#include "synchronized.h"

#include <vector>
#include <map>
#include <string>
#include <deque>
#include <set>

class InvertedIndex
{
public:
    using docid_t = size_t;
    using wordOccurence_t = size_t;
    using wordInfo_t = std::map<docid_t, wordOccurence_t>;
    using index_t = std::map<std::string_view, wordInfo_t>;
    using docs_t = std::deque<std::string>;

public:
    void Add(std::string &&document, size_t docid);
    const wordInfo_t Lookup(const std::string_view &word);

public:
    void AddWordOccurence(wordInfo_t &wordInfo, const size_t docid);
    std::string &GetDocument(const size_t id);
    size_t GetDocsCount();
    index_t GetIndex()
    {
        return index;
    }

private:
    index_t index{};
    docs_t docs;
};
