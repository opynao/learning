#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

std::vector<std::string_view> SplitIntoWords(std::string_view line)
{
  std::vector<std::string_view> result;

  size_t pos = line.find_first_not_of(' ');
  line.remove_prefix(pos);
  while (pos != line.npos)
  {
    pos = line.find(' ');
    result.push_back(line.substr(0, pos));
    pos = line.find_first_not_of(' ', pos);
    line.remove_prefix(pos);
  }

  return result;
}

SearchServer::SearchServer(istream &document_input)
{
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input)
{
  InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document);)
  {
    new_index.Add(move(current_document));
  }

  std::swap(index, new_index);
}

void SearchServer::AddQueriesStream(
    istream &query_input, ostream &search_results_output)
{
  std::vector<size_t> docid_count(index.GetDocsNumber(), 0);
  for (string current_query; getline(query_input, current_query);)
  {
    for (const auto &word : SplitIntoWords(current_query))
    {
      for (const auto &entry : index.Lookup(word))
        docid_count[entry.docid] += entry.wordOccurence;
    }

    vector<size_t> idx(docid_count.size());
    std::iota(idx.begin(), idx.end(), 0);

    auto it = idx.begin();
    std::advance(it, std::min<size_t>(5, docid_count.size()));

    std::partial_sort(idx.begin(), it, idx.end(),
                      [&docid_count](auto lhs, auto rhs) {
                        if (docid_count[lhs] == docid_count[rhs])
                          return lhs < rhs;
                        return docid_count[lhs] > docid_count[rhs];
                      });

    search_results_output << current_query << ":";

    for (size_t i = 0; i != std::min<size_t>(5, idx.size()); ++i)
    {
      size_t hitcount = docid_count[idx[i]];
      if (hitcount != 0)
      {
        search_results_output << " {"
                              << "docid: " << idx[i] << ", "
                              << "hitcount: " << hitcount << '}';
      }
    }
    search_results_output << "\n";
    docid_count.assign(index.GetDocsNumber(), 0);
  }
}

void InvertedIndex::Add(string &&document)
{
  docs.push_back(std::move(document));

  size_t docid = docs.size() - 1;

  for (const auto &word : SplitIntoWords(docs.back()))
  {
    auto& wordInfo = index[word];
    if (!wordInfo.empty() && wordInfo.back().docid == docid)
      ++wordInfo.back().wordOccurence;
    else
    {
      Entry entry;
      entry.docid = docid;
      entry.wordOccurence = 1;
      wordInfo.push_back(entry);
    }
  }
}

  const vector<Entry> &InvertedIndex::Lookup(const string_view &word) const
  {
    static const std::vector<Entry> empty;
    if (auto it = index.find(word); it != index.end())
    {
      return it->second;
    }
    return empty;
  }