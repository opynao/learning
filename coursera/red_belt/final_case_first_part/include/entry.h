#pragma once
#include <cstdio>

using wordOccurence_t = size_t;
using docid_t = size_t;

struct Entry
{
  docid_t docid{};
  wordOccurence_t wordOccurence{};
};