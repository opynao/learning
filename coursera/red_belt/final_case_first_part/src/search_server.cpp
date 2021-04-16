#include "search_server.h"
#include "iterator_range.h"
#include "split_into_words.h"

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

void SearchServer::AddQueriesStream(
    input_t &query_input, output_t &search_results_output)
{
  LOGF;
  std::vector<std::future<std::string>> futures;

  for (query_t current_query; std::getline(query_input, current_query);)
  {
    futures.push_back(std::async([this,
                                  current_query]() {
      const auto &words = SplitIntoWords(current_query);
      auto docid_count = BuildDocidWordOccurence(words);
      docidCount_t copy;
      std::ostringstream oss;
      //PrintResults(oss, current_query, CalculateDocidPosition(docid_count), docid_count);
      //auto it = docid_count.begin();

      //std::advance(it, std::min<size_t>(5, docid_count.size()));
      for (size_t i = 0; i != std::min<size_t>(5, docid_count.size()); ++i)
      {
        auto it = std::max_element(docid_count.begin(), docid_count.end(), [](const auto &lhs, const auto &rhs) {
          if (lhs.second == rhs.second)
            return lhs.first < rhs.first;
          return lhs.second > rhs.second;
        });
        copy[it->first] = it->second;
        docid_count.erase(it);
      }

      /* std::partial_sort(docid_count.begin(), it, docid_count.end(), [](const auto &lhs, const auto &rhs) {
        if (lhs.wordOccurence == rhs.wordOccurence)
          return lhs.docid < rhs.docid;
        return lhs.wordOccurence > rhs.wordOccurence;
      });*/
      PrintResults(oss, current_query, copy);
      LOGF;

      return oss.str();
    }));
  }
  LOGF;

  for (auto &future : futures)
    search_results_output << future.get();
  LOGF;
}

SearchServer::docidCount_t SearchServer::BuildDocidWordOccurence(
    const std::vector<std::string_view> &words)
{
  LOGF;
  const auto &rIndex = index_.GetAccess();
  if (words.size() == 1)
    return rIndex.ref_to_value.Lookup(*words.begin());

  docidCount_t docid_count{};

  std::for_each(words.cbegin(), words.cend(), [&docid_count, &rIndex](const auto &word) {
    const auto &wordInfo = rIndex.ref_to_value.Lookup(word);
    for (auto it = wordInfo.begin(); it != wordInfo.end(); ++it)
    {
   /*   auto itFind = std::find_if(docid_count.begin(), docid_count.end(),
                                 [&it](const auto &entry) { return entry.docid == it->docid; });
      if (itFind == docid_count.end())
        docid_count.push_back(*it);
      else
        itFind->wordOccurence += it->wordOccurence;*/
       for (auto &wordI : wordInfo)
          docid_count[wordI.first] += wordI.second;
      //Resize(wordInfo, docid_count);
      //Transform(wordInfo, docid_count);
    } });

  return docid_count;
}
/*
void SearchServer::Resize(const docidCount_t &wordInfo, docidCount_t &docid_count)
{
  const auto size = std::max(wordInfo.size(), docid_count.size());
  if (docid_count.size() < size)
    docid_count.resize(size + 1);
}

void SearchServer::Transform(const docidCount_t &wordInfo, docidCount_t &docid_count)
{
  std::transform(wordInfo.cbegin(),
                 wordInfo.cbegin() + wordInfo.size(),
                 docid_count.cbegin(),
                 docid_count.begin(),
                 std::plus<size_t>());
}
*/
std::vector<size_t> SearchServer::CalculateDocidPosition(docidCount_t &docid_count)
{
  std::vector<size_t> docid_position(docid_count.size());
  std::iota(docid_position.begin(), docid_position.end(), 0);
  // PartialSort(docid_count, docid_position);
  return docid_position;
}
/*
void SearchServer::PartialSort(docidCount_t &docid_count, docidPosition_t &docid_position)
{
  auto it = docid_position.begin();
  std::advance(it, std::min<size_t>(5, docid_count.size()));
  std::partial_sort(docid_position.begin(), it, docid_position.end(),
                    [&docid_count](auto lhs, auto rhs) {
                      if (docid_count[lhs] == docid_count[rhs])
                        return lhs < rhs;
                      return docid_count[lhs] > docid_count[rhs];
                    });
}*/
/*
void SearchServer::PrintResults(
    output_t &search_results_output,
    const query_t &current_query,
    const docidPosition_t &docid_position,
    docidCount_t &docid_count)
{
  search_results_output << current_query << ":";
  for (size_t i = 0; i != std::min<size_t>(5, docid_position.size()); ++i)
  {
    auto hitcount = docid_count[docid_position[i]];
    if (hitcount)
    {
      search_results_output << " {"
                            << "docid: " << docid_position[i] << ", "
                            << "hitcount: " << hitcount << '}';
    }
  }
  search_results_output << "\n";
}
*/

void SearchServer::PrintResults(
    output_t &search_results_output,
    const query_t &current_query,
    docidCount_t &docid_count)
{
  search_results_output << current_query << ":";
  for (auto itBegin = docid_count.rbegin(); itBegin != docid_count.rend(); ++itBegin)
  {
    LOGF;
    if (itBegin->second)
    {
      search_results_output << " {"
                            << "docid: " << itBegin->first << ", "
                            << "hitcount: " << itBegin->second << '}';
    }
  }
  LOGF;
  std::string content;
  search_results_output << "\n";
  std::stringstream ss;
  ss << search_results_output.rdbuf();
  content = ss.str();
  PR(content);
}

InvertedIndex &SearchServer::GetIndex()
{
  return index_.GetAccess().ref_to_value;
}