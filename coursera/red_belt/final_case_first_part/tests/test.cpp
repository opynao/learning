#include "search_server.h"
#include "parse.h"
#include "gtest/gtest.h"
#include "iterator_range.h"
#include "profile.h"
#include "split_into_words.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <thread>

using namespace std;

void TestFunctionality(
    const vector<string> &docs,
    const vector<string> &queries,
    const vector<string> &expected)
{
  istringstream docs_input(Join('\n', docs));
  istringstream queries_input(Join('\n', queries));
  SearchServer srv;
  srv.UpdateDocumentBase(docs_input);
  ostringstream queries_output;
  srv.AddQueriesStream(queries_input, queries_output);

  const string result = queries_output.str();
  PR(result);
  const auto lines = SplitBy(Strip(result), '\n');

  EXPECT_EQ(lines.size(), expected.size());
  for (size_t i = 0; i < lines.size(); ++i)
  {
    EXPECT_EQ(lines[i], expected[i]);
  }
}

TEST(Basic, SerpFormat)
{
  const vector<string> docs = {
      "london is the capital of great britain",
      "i am travelling down the river"};
  const vector<string> queries = {"london", "the"};
  const vector<string> expected = {
      "london: {docid: 0, hitcount: 1}",
      Join(' ', vector{
                    "the:",
                    "{docid: 0, hitcount: 1}",
                    "{docid: 1, hitcount: 1}"})};

  TestFunctionality(docs, queries, expected);
}

TEST(Basic, Top5)
{
  const vector<string> docs =
      {
          "milk a",
          "milk b",
          "milk c",
          "milk d",
          "milk e",
          "milk f",
          "milk g",
          "water a",
          "water b",
          "fire and earth"};

  const vector<string> queries = {"milk", "water", "rock"};
  const vector<string> expected =
      {
          Join(' ', vector{
                        "milk:",
                        "{docid: 0, hitcount: 1}",
                        "{docid: 1, hitcount: 1}",
                        "{docid: 2, hitcount: 1}",
                        "{docid: 3, hitcount: 1}",
                        "{docid: 4, hitcount: 1}"}),
          Join(' ', vector{
                        "water:",
                        "{docid: 7, hitcount: 1}",
                        "{docid: 8, hitcount: 1}",
                    }),
          "rock:",
      };
  TestFunctionality(docs, queries, expected);
}

TEST(Basic, Hitcount)
{
  const vector<string> docs = {
      "the river goes through the entire city there is a house near it",
      "the wall",
      "walle",
      "is is is is",
  };
  const vector<string> queries = {"the", "wall", "all", "is", "the is"};
  const vector<string> expected = {
      Join(' ', vector{
                    "the:",
                    "{docid: 0, hitcount: 2}",
                    "{docid: 1, hitcount: 1}",
                }),
      "wall: {docid: 1, hitcount: 1}",
      "all:",
      Join(' ', vector{
                    "is:",
                    "{docid: 3, hitcount: 4}",
                    "{docid: 0, hitcount: 1}",
                }),
      Join(' ', vector{
                    "the is:",
                    "{docid: 3, hitcount: 4}",
                    "{docid: 0, hitcount: 3}",
                    "{docid: 1, hitcount: 1}",
                }),
  };
  TestFunctionality(docs, queries, expected);
}

TEST(Basic, Ranking)
{
  const vector<string> docs = {
      "london is the capital of great britain",
      "paris is the capital of france",
      "berlin is the capital of germany",
      "rome is the capital of italy",
      "madrid is the capital of spain",
      "lisboa is the capital of portugal",
      "bern is the capital of switzerland",
      "moscow is the capital of russia",
      "kiev is the capital of ukraine",
      "minsk is the capital of belarus",
      "astana is the capital of kazakhstan",
      "beijing is the capital of china",
      "tokyo is the capital of japan",
      "bangkok is the capital of thailand",
      "welcome to moscow the capital of russia the third rome",
      "amsterdam is the capital of netherlands",
      "helsinki is the capital of finland",
      "oslo is the capital of norway",
      "stockgolm is the capital of sweden",
      "riga is the capital of latvia",
      "tallin is the capital of estonia",
      "warsaw is the capital of poland",
  };

  const vector<string> queries = {"moscow is the capital of russia"};
  const vector<string> expected = {
      Join(' ', vector{
                    "moscow is the capital of russia:",
                    "{docid: 7, hitcount: 6}",
                    "{docid: 14, hitcount: 6}",
                    "{docid: 0, hitcount: 4}",
                    "{docid: 1, hitcount: 4}",
                    "{docid: 2, hitcount: 4}",
                })};
  TestFunctionality(docs, queries, expected);
}

TEST(Basic, BasicSearch)
{
  const vector<string> docs = {
      "we are ready to go",
      "come on everybody shake you hands",
      "i love this game",
      "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
      "daddy daddy daddy dad dad dad",
      "tell me the meaning of being lonely",
      "just keep track of it",
      "how hard could it be",
      "it is going to be legen wait for it dary legendary",
      "we dont need no education"};

  const vector<string> queries = {
      "we need some help",
      "it",
      "i love this game",
      "tell me why",
      "dislike",
      "about"};

  const vector<string> expected = {
      Join(' ', vector{
                    "we need some help:",
                    "{docid: 9, hitcount: 2}",
                    "{docid: 0, hitcount: 1}"}),
      Join(' ', vector{
                    "it:",
                    "{docid: 8, hitcount: 2}",
                    "{docid: 6, hitcount: 1}",
                    "{docid: 7, hitcount: 1}",
                }),
      "i love this game: {docid: 2, hitcount: 4}",
      "tell me why: {docid: 5, hitcount: 2}",
      "dislike:",
      "about: {docid: 3, hitcount: 2}",
  };
  TestFunctionality(docs, queries, expected);
}

istringstream gen_random()
{
  const int len{10};
  string tmp_s;
  static const char alphanum[] =
      "abcdefghijklmnopqrstuvwxyz";

  tmp_s.reserve(10 * 5000 * len);
  for (int j = 0; j != 5000; ++j)
  {
    for (int i = 0; i != 10; ++i)
    {
      for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

      tmp_s += " ";
    }
    tmp_s += "\n";
  }
  istringstream is(tmp_s);
  return is;
}

istringstream gen_random_doc()
{
  const int len{10};
  string tmp_s;
  static const char alphanum[] =
      "abcdefghijklmnopqrstuvwxyz";

  tmp_s.reserve(150 * len);
  for (int j = 0; j != 15; ++j)
  {
    for (int i = 0; i != 10; ++i)
    {
      for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];

      tmp_s += " ";
    }
    tmp_s += "\n";
  }
  istringstream is(tmp_s);
  return is;
}

TEST(Duration, SplitIntoWords)
{
  auto queries = gen_random();
  {
    LOG_DURATION("SplitIntoWords");
    for (string current_query; getline(queries, current_query);)
      SplitIntoWords(current_query);
  }
}
/*
TEST(Duration, SearchIndex)
{
  istringstream docs_input = gen_random_doc();
  auto queries_input = gen_random();
  SearchServer srv;
  srv.UpdateDocumentBase(docs_input);
  ostringstream queries_output;
  {
    LOG_DURATION(" Split + Search ");
    for (string current_query; getline(queries_input, current_query);)
    {
      const auto words = SplitIntoWords(current_query);
      std::vector<size_t> docid_count;

      for (const auto &word : words)
      {
        for (const auto &entry : srv.GetIndex().Lookup(word))
          docid_count[entry.docid] += entry.wordOccurence;
      }
    }
  }
}
*/

TEST(Duration, All)
{
  istringstream docs_input = gen_random_doc();
  auto queries_input = gen_random();
  std::ostringstream oss{};
  SearchServer srv;
  {
    //LOG_DURATION("All");
    srv.UpdateDocumentBase(docs_input);
    srv.AddQueriesStream(queries_input, oss);
  }
}

/*
TEST(Basic, SearchServer)
{

  std::vector<std::pair<std::istringstream, std::ostringstream *>> streams;
  streams.push_back({gen_random_doc(), {}});
  streams.push_back({gen_random_doc(), {}});
  // IteratorRange — шаблон из задачи Paginator
  // random_time() — функция, которая возвращает случайный
  // промежуток времени

  LOG_DURATION("Total");
  SearchServer srv(streams.front().first);
  for (auto &[input, output] :
       IteratorRange(begin(streams) + 1, end(streams)))
  {
    this_thread::sleep_for(std::random_time());
    if (!output)
      srv.UpdateDocumentBase(input);
    else
      srv.AddQueriesStream(input, *output);
  }
}*/
