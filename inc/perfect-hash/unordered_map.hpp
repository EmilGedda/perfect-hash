#ifndef PERFECT_HASH_UNORDERED_MAP_HPP
#define PERFECT_HASH_UNORDERED_MAP_HPP

#include <array>
#include <initializer_list>
#include <bitset>
#include <limits>
#include <memory>
#include <functional>
#include <utility>

namespace perfecthash {

  inline namespace v1 {

    namespace universal {

      template<
        class Key,
        class T,
        class Hash,
        std::size_t Size
      > class unordered_map : public std::array<T, Size> {

        using array = std::array<T, Size>;
        using value_type = std::pair<const Key, T>;
        using key_type = Key;
        using mapped_type = T;
        using hasher = Hash;

        int seed = 0;

      public:
        unordered_map(std::initializer_list<value_type> values) {
          for (this->seed = 0; seed < std::numeric_limits<decltype(seed)>::max(); seed++) {
            std::bitset<Size> index_filter;
            Hash hashfn(seed);
            for (auto& value : values) {
              auto&& busy_index = index_filter[hashfn(value.first) % Size];
              if (busy_index) goto next;
              busy_index = true;
            }
            break;
          next:
            continue;
          }

          int i = 0;
          for (auto& value : values) {
            array::operator[](i++) = std::move(value.second);
          }
        }

        const T& operator[](const Key& key) const noexcept {
          return array::operator[](Hash(this->seed)(key) % Size);
        }

        T& operator[](const Key& key) noexcept {
          return array::operator[](Hash(this->seed)(key) % Size);
        }

      };

    }
  }
}

#endif // PERFECT_HASH_UNORDERED_MAP_HPP
