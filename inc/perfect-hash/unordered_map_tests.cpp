#ifndef PERFECT_HASH_UNORDERED_MAP_TESTS_HPP
#define PERFECT_HASH_UNORDERED_MAP_TESTS_HPP

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "unordered_map.hpp"

struct counting_hash {
  explicit constexpr counting_hash(int) { }

  constexpr int operator()(const char& c) { 
    return c - '1';
  }
};

TEST_CASE("unordered_map creation") {

  constexpr std::initializer_list<std::pair<const char, int>> init{
      {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}
  };

  constexpr auto table = perfecthash::universal::unordered_map<char, int, counting_hash, 5>(init);

  for (auto& pair : init)
    CHECK(table[pair.first] == pair.second);
}

#endif // PERFECT_HASH_UNORDERED_MAP_TESTS_HPP