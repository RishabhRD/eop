#include <functional>
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

template<std::input_iterator Iter,
  typename T,
  eop::callable_with<iterator::value_type<Iter>> Projection = std::identity,
  eop::callable_with_return<T,
    T,
    std::invoke_result_t<Projection, iterator::value_type<Iter>>> BinaryOp =
    std::plus<int>>
auto reduce(Iter first,
  Iter last,
  T init,
  BinaryOp op = std::plus<int>{},
  Projection proj = std::identity{}) {
  // precondition : bounded_range [first, last)
  // precondition : op -> partially associative
  for (; first != last; ++first) { init = op(std::move(init), proj(*first)); }
  return init;
}

template<std::input_iterator Iter,
  eop::callable_with<iterator::value_type<Iter>> Func>
std::pair<Func, Iter>
  for_each_n(Iter first, iterator::difference_type<Iter> n, Func func) {
  // precondition: readable weak range [first, n)
  for (; n > 0; --n, ++first) { func(*first); }
  return std::pair{ func, first };
}

template<std::input_iterator Iter,
  std::same_as<iterator::value_type<Iter>> Value>
auto find(Iter first, iterator::difference_type<Iter> n, Value const &val) {
  // precondition: readable weak range [first, n)
  while (n > 0 && *first != val) {
    ++first;
    --n;
  }
  return std::pair{ n, first };
}

template<std::input_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
Iter find_if(Iter first,
  iterator::difference_type<Iter> n,
  Predicate predicate) {
  // precondition: readable weak range [first, n)
  while (n > 0 && !predicate(*first)) {
    ++first;
    --n;
  }
  return std::pair{ n, first };
}

template<std::input_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Relation =
    std::equal_to<iterator::value_type<Iter>>>
auto mismatch(Iter f1,
  Iter l1,
  Iter f2,
  Iter l2,
  Relation eq = std::equal_to<iterator::value_type<Iter>>{}) {
  // pre: readable bounded range [f1, l1)
  // pre: readable bounded range [f2, l2)
  while (f1 != l1 and f2 != l2 and eq(*f1, *f2)) {
    ++f1;
    ++f2;
  }
  return std::pair{ f1, f2 };
  // post: (f1 == l1) || (f2 == l2) || !eq(*f1, *f2)
}

template<std::input_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Relation =
    std::equal_to<iterator::value_type<Iter>>>
auto adjacent_mismatch(Iter f,
  Iter l,
  Relation eq = std::equal_to<iterator::value_type<Iter>>{}) {
  // pre: readable bounded range [f, l)
  // Its important to copy, as once moved forward, (f - 1) is invalidated
  if (f == l) return l;
  auto prev = *f;
  ++f;
  while (f != l and eq(prev, *f)) {
    prev = *f;
    ++f;
  }
  return f;
  // post: (f == l) || !eq(prev, *f)
}

template<std::forward_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Relation =
    std::equal_to<iterator::value_type<Iter>>>
auto adjacent_mismatch(Iter f,
  Iter l,
  Relation eq = std::equal_to<iterator::value_type<Iter>>{}) {
  // pre: readable bounded range [f, l)
  if (f == l) return l;
  auto prev = f;
  ++f;
  while (f != l and eq(*prev, *f)) {
    prev = f;
    ++f;
  }
  return f;
  // post: (f == l) || !eq(*prev, *f)
}

template<std::input_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Relation>
auto relation_preserving(Iter f, Iter l, Relation r) {
  return adjacent_mismatch(f, l, r) == l;
}

template<std::input_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Relation>
auto strictly_increasing_range(Iter f, Iter l, Relation r) {
  return relation_preserving(f, l, r);
}

template<std::input_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Relation>
auto increasing_range(Iter f, Iter l, Relation r) {
  return relation_preserving(f,
    l,
    [r = std::move(r)](auto const &a, auto const &b) { return !r(b, a); });
}

/*
 * If a range is p-partitioned, all elements that satisfies predicate
 * followed by only elements that don't satisfy predicate.
 *
 * Also if we had regular iterators, we could have thought for binary search.
 */
template<std::input_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
auto is_partitioned(Iter f, Iter l, Predicate p) {
  return none_of(find_if_not(f, l, p), l, p);
}

template<std::forward_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
auto partition_point_n(Iter f, iterator::difference_type<Iter> n, Predicate p) {
  while (n != 0) {
    auto h = n / 2;
    auto m = std::advance(f, h);
    if (p(*m)) {
      f = m;
      ++f;
      n = n - h + 1;
    } else {
      n = h;
    }
  }
}

template<std::forward_iterator Iter,
  eop::predicate<iterator::value_type<Iter>> Predicate>
auto partition_point(Iter f, Iter l, Predicate p) {
  return partition_point_n(f, std::distance(f, l), p);
}

template<std::forward_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Comparator =
    std::less<iterator::value_type<Iter>>>
auto lower_bound(Iter f,
  Iter l,
  iterator::value_type<Iter> const &val,
  Comparator comp = std::less<iterator::value_type<Iter>>{}) {
  return partition_point(f, l, [&](auto const &ele) { return comp(ele, val); });
}

template<std::forward_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Comparator =
    std::less<iterator::value_type<Iter>>>
auto upper_bound(Iter f,
  Iter l,
  iterator::value_type<Iter> const &val,
  Comparator comp = std::less<iterator::value_type<Iter>>{}) {
  return partition_point(
    f, l, [&](auto const &ele) { return !comp(val, ele); });
}

template<std::forward_iterator Iter,
  eop::relation<iterator::value_type<Iter>> Comparator =
    std::less<iterator::value_type<Iter>>>
auto equal_range(Iter f,
  Iter l,
  iterator::value_type<Iter> const &val,
  Comparator comp = std::less<iterator::value_type<Iter>>{}) {
  auto left = lower_bound(f, l, val, comp);
  auto right = upper_bound(left, l, val, comp);
  return std::pair{ left, right };
}


};// namespace stl
