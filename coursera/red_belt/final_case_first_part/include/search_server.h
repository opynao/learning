#pragma once

#include "inverted_index.h"
#include "synchronized.h"
#include "profile.h"

#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <stack>
#include <cassert>
#include <set>
#include <cstdint>
#include <future>

#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__
#define PR(x) std::cerr << #x << " = " << x << std::endl
#define LOGFSTART LOGF << " " << i << " START" << std::endl
#define LOGFEND LOGF << " " << i++ << " END" << std::endl

enum class State
{
  start,
  stop
};

struct
{
  int write_;
  int read_;
  void write(State state)
  {
    if (state == State::start)
      write_++;
    else
      write_--;
  }
  void read(State state)
  {
    if (state == State::start)
      read_++;
    else
      read_--;
  }
  void swap()
  {
    assert(!write_ && !read_);
  }
} Stack;

using input_t = std::istream;
using output_t = std::ostream;
using query_t = std::string;
using docidCount_t = std::vector<uint16_t>;
using words_t = std::vector<std::string_view>;

class SearchServer
{
public:
  SearchServer() = default;
  explicit SearchServer(input_t &document_input);
  void UpdateDocumentBase(input_t &document_input);

private:
  void CreateNewIndex(input_t &document_input);
  void ClearNewIndex();
  void FillNewIndex(input_t &document_input);

public:
  void AddQueriesStream(input_t &query_input, output_t &search_results_output);

private:
  void PrintResults(output_t &search_results_output,
                    const query_t &current_query,
                    const std::multiset<Entry> &docid_count);

  //docidCount_t BuildDocidWordOccurence(const words_t &words);
  docidCount_t BuildDocidWordOccurence(const std::vector<std::string> &words);

public:
  InvertedIndex &GetIndex()
  {
    return index_.GetAccess().ref_to_value;
  }

private:
  Synchronized<InvertedIndex> index_;
  std::vector<std::future<void>> futures;
  Synchronized<InvertedIndex> new_index_;
};