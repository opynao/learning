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

class SearchServer
{
public:
  using input_t = std::istream;
  using output_t = std::ostream;
  using query_t = std::string;
  using docidCount_t = std::map<size_t, size_t>;
  using docidPosition_t = std::vector<size_t>;
  using words_t = std::vector<std::string_view>;

public:
  SearchServer() = default;
  explicit SearchServer(input_t &document_input);
  void UpdateDocumentBase(input_t &document_input);
  void AddQueriesStream(input_t &query_input, output_t &search_results_output);

public:
  InvertedIndex &GetIndex();

private:
  static docidPosition_t CalculateDocidPosition(docidCount_t &docid_count);
  // static void PartialSort(docidCount_t &docid_count, docidPosition_t &docid_position);

  /* void PrintResults(output_t &search_results_output,
                    const query_t &current_query,
                    const docidPosition_t &docid_position,
                    docidCount_t &docid_count);*/
  void PrintResults(output_t &search_results_output,
                    const query_t &current_query,
                    docidCount_t &docid_count);

  docidCount_t BuildDocidWordOccurence(const words_t &words);
  void CreateNewIndex(input_t &document_input);
  void ClearNewIndex();
  void FillNewIndex(input_t &document_input);
  // void Resize(const docidCount_t &wordInfo, docidCount_t &docid_count);
  // void Transform(const docidCount_t &wordInfo, docidCount_t &docid_count);

private:
  Synchronized<InvertedIndex> index_;
  Synchronized<InvertedIndex> new_index_;
};