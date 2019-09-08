#ifndef PERFECT_HASH_UNORDERED_MAP_TESTS_HPP
#define PERFECT_HASH_UNORDERED_MAP_TESTS_HPP

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <array>
#include <utility>

#include "unordered_map.hpp"

struct counting_hash {
  explicit constexpr counting_hash(int) { }

  constexpr int operator()(const char& c) { 
    return c - '1';
  }
};

TEST_CASE("unordered_map creation") {

  constexpr std::array<std::pair<char, int>, 5> init = { 
    std::pair{'1', 1}, // AppleClang cannot deduce the init-list properly without the explicit type here.
    {'2', 2}, 
    {'3', 3},
    {'4', 4},
    {'5', 5} 
  };

  constexpr auto table = perfecthash::universal::unordered_map<char, int, counting_hash, 5>(init);

  for (const auto& pair : init)
    CHECK(table[pair.first] == pair.second);
}

#endif // PERFECT_HASH_UNORDERED_MAP_TESTS_HPP