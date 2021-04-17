#pragma once
#include <cstdio>
#include <cstdint>

using wordOccurence_t = int32_t;
using docid_t = int16_t;

struct Entry
{
  Entry(docid_t d, wordOccurence_t w)
      : docid{d}, wordOccurence{w}
  {
  }
  docid_t docid{};
  wordOccurence_t wordOccurence{};
};

bool operator<(const Entry &lhs, const Entry &rhs);