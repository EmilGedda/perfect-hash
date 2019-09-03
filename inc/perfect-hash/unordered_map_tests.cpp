#ifndef PERFECT_HASH_UNORDERED_MAP_TESTS_HPP
#define PERFECT_HASH_UNORDERED_MAP_TESTS_HPP

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include "unordered_map.hpp"

int seed = 0;

struct counting_hash {
  counting_hash(int) { }
  template<typename T>
  int operator()(const T&) { return seed++; }

  static void reset() { seed = 0; }
};

TEST_CASE("unordered_map creation") {

  auto init = std::initializer_list<std::pair<const char, int>>{
      {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}
  };

  auto table = perfecthash::universal::unordered_map<char, int, counting_hash, 5>(init);

  counting_hash::reset();

  for (auto& pair : init)
    CHECK(table[pair.first] == pair.second);
}

#endif // PERFECT_HASH_UNORDERED_MAP_TESTS_HPP