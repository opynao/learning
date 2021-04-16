#include "inverted_index.h"
#include "split_into_words.h"
#include "search_server.h"

#include <algorithm>
#include <mutex>

void InvertedIndex::Add(std::string &&document, size_t docid)
{
  if (!docs.size() || (docs.size() - 1) < docid)
    docs.resize(docid + 1, "");

  docs[docid] = std::move(document);

  for (const auto &word : SplitIntoWords(docs[docid]))
  {
    auto &wordInfo = index[word];
    AddWordOccurence(wordInfo, docid);
  }
}

const InvertedIndex::wordInfo_t InvertedIndex::Lookup(const std::string_view &word)
{
  //static const std::vector<size_t> empty;
  if (auto it = index.find(word); it != index.cend())
    return it->second;
  return {};
}

void InvertedIndex::AddWordOccurence(wordInfo_t &wordInfo, const size_t docid)
{
/*  auto it = std::find_if(wordInfo.begin(), wordInfo.end(), [&docid](const auto &entry) { return entry.docid == docid; });
  if (it == wordInfo.end())
  {
    Entry entry;
    entry.docid = docid;
    entry.wordOccurence = 1;
    wordInfo.push_back(entry);
  }
  else
    ++it->wordOccurence;*/
  ++wordInfo[docid];
}

std::string &InvertedIndex::GetDocument(const size_t id)
{
  return docs[id];
}

size_t InvertedIndex::GetDocsCount()
{
  return docs.size();
}
