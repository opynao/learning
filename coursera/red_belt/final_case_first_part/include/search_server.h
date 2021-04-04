#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
using namespace std;

#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl
#define PR(x) std::cerr << #x << " = " << x << std::endl
using wordOccurence_t = size_t;
using docid_t = size_t;

struct Entry
{
  docid_t docid{};
  wordOccurence_t wordOccurence{};
};

class InvertedIndex
{
public:
  void Add(std::string &&document);
  const vector<Entry> &Lookup(const string_view &word) const;

  const string &GetDocument(size_t id) const
  {
    return docs[id];
  }
  size_t GetDocsNumber() const
  {
    return docs.size();
  }

private:
  map<std::string_view, std::vector<Entry>> index{};
  std::deque<string> docs{};
};

class SearchServer
{
public:
  SearchServer() = default;
  explicit SearchServer(istream &document_input);
  void UpdateDocumentBase(istream &document_input);
  void AddQueriesStream(istream &query_input, ostream &search_results_output);
  InvertedIndex GetIndex() const
  {
    return index;
  }

private:
  InvertedIndex index;
};

std::vector<std::string_view> SplitIntoWords(std::string_view line);