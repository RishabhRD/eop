#include <concepts>
#include <iterator>
#include "concepts.hpp"

namespace stl {

namespace iterator {
  template<typename Iter>
  using value_type = typename std::iterator_traits<Iter>::value_type;

  template<typename Iter>
  using difference_type = typename std::iterator_traits<Iter>::difference_type;
};// namespace iterator

template<std::input_iterator Iter,
  eop::callable_with<iterator::value_type<Iter>> Func>
Func for_each(Iter first, Iter last, Func func) {
  // precondition: readable bounded range [first, last)
  while (first != last) {
    func(*first);
    ++first;
  }
  return func;
}

template<std::input_iterator Iter,
  std::same_as<iterator::value_type<Iter>> Value>
Iter find(Iter first, Iter last, Value const &val) {
  // precondition: readable bounded range [first, last)
  while (first != last && *first != val) { ++first; }
  return first;
}

template<std::input_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
Iter find_if(Iter first, Iter last, Predicate predicate) {
  // precondition: readable bounded range [first, last)
  while (first != last && !predicate(*first)) { ++first; }
  return first;
}

template<std::input_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
Iter find_if_not(Iter first, Iter last, Predicate predicate) {
  // precondition: readable bounded range [first, last)
  while (first != last && predicate(*first)) { ++first; }
  return first;
}

template<std::input_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
bool all_of(Iter first, Iter last, Predicate predicate) {
  // precondition: readable bounded range [first, last)
  return find_if_not(first, last, predicate) == last;
}

template<std::input_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
bool none_of(Iter first, Iter last, Predicate predicate) {
  // precondition: readable bounded range [first, last)
  return find_if(first, last, predicate) == last;
}

template<std::input_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
bool any_of(Iter first, Iter last, Predicate predicate) {
  // precondition: readable bounded range [first, last)
  return find_if(first, last, predicate) != last;
}

template<std::input_iterator Iter,
  std::same_as<iterator::value_type<Iter>> Value>
auto count(Iter first, Iter last, Value const &val) {
  // precondition: readable bounded range [first, last)
  iterator::difference_type<Iter> cnt{ 0 };
  for (; first != last; ++first) {
    if (*first == val) ++cnt;
  }
  return cnt;
}

template<std::input_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
auto count_if(Iter first, Iter last, Predicate p) {
  // precondition: readable bounded range [first, last)
  iterator::difference_type<Iter> cnt{ 0 };
  for (; first != last; ++first) {
    if (p(*first)) ++cnt;
  }
  return cnt;
}


};// namespace stl
