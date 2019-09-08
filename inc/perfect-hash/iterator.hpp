#ifndef PERFECT_HASH_ITERATOR_HPP
#define PERFECT_HASH_ITERATOR_HPP
namespace perfecthash {

  inline namespace v1 {
    namespace pair {

      struct first {
        template<typename T, typename U>
        static auto get(const std::pair<T, U>& p) noexcept {
          return std::get<0>(p);
        }
      };

      struct second {
        template<typename T, typename U>
        static U& get(const std::pair<T, U>& p) noexcept { return p.second; }
      };

      template<typename Side, typename PairIt>
      struct iterator {
        PairIt it;
        explicit constexpr iterator(const PairIt& it) : it(it) { }
        auto& operator*() noexcept { return Side::get(*it); }
        const auto& operator*() const noexcept { return Side::get(*it); }
      };
      template<typename Side, typename It>
      iterator(const It& it)->iterator<Side, It>;
    }
  }
}

#endif // PERFECT_HASH_ITERATOR_HPP