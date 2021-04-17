#include "search_server.h"
#include "split_into_words.h"
#include "concurrent_map.h"

#include <condition_variable>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <numeric>
#include <future>

SearchServer::SearchServer(input_t &document_input)
{
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(input_t &document_input)
{
  CreateNewIndex(document_input);
  const auto &rIndex = index_.GetAccess();
  const auto &rNewIndex = new_index_.GetAccess();
  rIndex.ref_to_value = std::move(rNewIndex.ref_to_value);
}

void SearchServer::CreateNewIndex(input_t &document_input)
{
  ClearNewIndex();
  FillNewIndex(document_input);
}

void SearchServer::ClearNewIndex()
{
  InvertedIndex new_index;
  const auto &rAccess = new_index_.GetAccess();
  rAccess.ref_to_value = std::move(new_index);
}

void SearchServer::FillNewIndex(input_t &document_input)
{
  std::vector<std::future<void>> futures;
  std::string current_document{};
  size_t docid{};

  for (; std::getline(document_input, current_document); ++docid)
  {
    futures.push_back(std::async([this, docid, current_document]() mutable {
      const auto &rAccess = new_index_.GetAccess();
      rAccess.ref_to_value.Add(std::move(current_document), docid);
    }));
  }
}
/*
void SearchServer::AddQueriesStream(
    input_t &query_input, output_t &search_results_output)
{
  std::vector<std::future<std::string>> futures;

  for (query_t current_query; std::getline(query_input, current_query);)
  {
    futures.push_back(std::async([this, current_query]() {
      const auto &words = SplitIntoWords(current_query);
      const auto &docIdCount = BuildDocidWordOccurence(words);
      std::multiset<Entry> s;
      uint16_t count{};
      for (const auto entry : docIdCount)
      {
        if (entry)
          s.emplace(count, entry);
        ++count;
      }
      std::ostringstream oss;
      PrintResults(oss, current_query, s);

      return oss.str();
    }));
  }

  for (auto &future : futures)
    search_results_output << future.get();
}
*/

void SearchServer::AddQueriesStream(
    input_t &query_input, output_t &search_results_output)
{
  std::vector<
      std::future<
          std::pair<
              std::string,
              std::vector<Entry>>>>
      futures;

  for (query_t current_query; std::getline(query_input, current_query);)
  {
    futures.push_back(std::async([this, current_query]() {
      const auto words = SplitIntoWords(current_query);
      docidCount_t docid_count = BuildDocidWordOccurence(words);

      std::multiset<Entry> s;
      uint16_t count{};
      for (const auto entry : docid_count)
      {
        if (entry)
          s.emplace(count, entry);
        ++count;
      }

      std::vector<Entry> v;
      const auto size = std::min<size_t>(5, s.size());
      auto itEnd = std::next(s.begin(), size);
      v.reserve(size);
      std::move(s.begin(), itEnd, std::back_inserter(v));

      return std::make_pair(current_query, v);
    }));
  }

  for (auto &future : futures)
  {
    const auto &result = future.get();
    search_results_output << result.first << ":";
    std::for_each(
        result.second.cbegin(), result.second.cend(),
        [&search_results_output](const auto &pr) mutable {
          search_results_output << " {"
                                << "docid: " << pr.docid << ", "
                                << "hitcount: " << pr.wordOccurence << '}';
        });
    search_results_output << "\n";
  }
}

docidCount_t SearchServer::BuildDocidWordOccurence(
    const std::vector<std::string> &words)
{
  const auto &rIndex = index_.GetAccess();
  if (words.size() == 1)
    return rIndex.ref_to_value.Lookup(*words.begin());
  docidCount_t docid_count;

  std::for_each(words.cbegin(), words.cend(), [&docid_count, &rIndex](const auto &word) {
    const auto &wordInfo = rIndex.ref_to_value.Lookup(word);
    if (wordInfo.size() > docid_count.size())
      docid_count.resize(wordInfo.size());
    for (size_t i = 0; i != wordInfo.size(); ++i)
      docid_count[i] += wordInfo[i];
  });

  return docid_count;
}

void SearchServer::PrintResults(output_t &search_results_output,
                                const query_t &current_query,
                                const std::multiset<Entry> &docid_count)
{
  search_results_output << current_query << ":";
  const auto itEnd = std::next(docid_count.cbegin(), std::min<size_t>(5, docid_count.size()));
  for (auto itBegin = docid_count.begin(); itBegin != itEnd; ++itBegin)
  {
    search_results_output << " {"
                          << "docid: " << itBegin->docid << ", "
                          << "hitcount: " << itBegin->wordOccurence << '}';
  }
  search_results_output << "\n";
}