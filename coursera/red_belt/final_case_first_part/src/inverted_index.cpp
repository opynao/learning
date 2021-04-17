#include "inverted_index.h"
#include "split_into_words.h"
#include "search_server.h"

#include <algorithm>
#include <mutex>

void InvertedIndex::Add(std::string &&document, docid_t docid)
{
  /*if (!docs.size() || (docs.size() - 1) < docid)
    docs.resize(docid + 1);

  docs[docid] = std::move(document);
*/
  //for (const auto &word : SplitIntoWords(docs[docid]))
  for (const auto &word : SplitIntoWords(document))
    AddWordOccurence(word, docid);
}

const InvertedIndex::wordInfo_t &InvertedIndex::Lookup(const word_t &word) const
{
  static const wordInfo_t empty;
  if (auto it = index.find(word); it != index.cend())
    return it->second;
  return empty;
}

void InvertedIndex::AddWordOccurence(const word_t &word, const docid_t docid)
{
  auto &wordInfo = index[word];
  if (wordInfo.size() < (docid + 1))
    wordInfo.resize(docid + 1);
  ++wordInfo[docid];
}