#ifndef PERFECT_HASH_UNORDERED_MAP_HPP
#define PERFECT_HASH_UNORDERED_MAP_HPP

#include <array>
#include <bitset>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <limits>
#include <memory>
#include <utility>

namespace perfecthash {

  inline namespace v1 {

    namespace universal {

      template <typename T>
      struct is_pair : std::false_type { };

      template <typename T, typename U>
      struct is_pair<std::pair<T, U>> : std::true_type { };

      template <typename T>
      constexpr bool is_pair_v = is_pair<T>::value;

      template <typename, typename = void>
      struct is_mapping : std::false_type { };

      template <typename It>
      struct is_mapping<It, std::enable_if_t<
        is_pair_v<typename std::iterator_traits<It>::value_type>
        >> : std::true_type { };

      template <typename T>
      constexpr bool is_mapping_v = is_mapping<T>::value;


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
        explicit constexpr unordered_map(const std::initializer_list<value_type>& values)
          : seed(unique_seed(values.begin(), values.end())), array() {
          auto i = 0;
          for (const auto& value : values) {
            array::operator[](i++) = value.second;
          }
        }

        constexpr auto& operator[](const Key& key) const noexcept {
          return array::operator[](Hash(this->seed)(key) % Size);
        }

        constexpr auto& operator[](const Key& key) noexcept {
          return array::operator[](Hash(this->seed)(key) % Size);
        }

        template<typename ItBegin, typename ItEnd,
          std::enable_if_t<is_mapping_v<ItBegin>, int> = 0>
          static constexpr int unique_seed(ItBegin begin, ItEnd end) noexcept {
          for (auto seed = 0; seed < std::numeric_limits<decltype(seed)>::max(); seed++) {
            uint64_t index_filter = 0;
            Hash hashfn(seed);
            for (auto it = begin; it != end; it++) {
              auto index = 1 << hashfn(it->first) % Size;
              if (index_filter & index) break;
              index_filter |= index;
            }
            if (index_filter == (1 << Size) - 1)
              return seed;
          }
          return -1;
        }

      };

    }
  }
}

#endif // PERFECT_HASH_UNORDERED_MAP_HPP
