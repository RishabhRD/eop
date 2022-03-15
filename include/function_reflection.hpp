#pragma once

#include <tuple>

namespace eop {
template<size_t I, typename R, typename... A> struct func_type;

template<typename R, typename A> struct func_type<0, auto(A)->R> {
  using return_t = R;
  using argument_t = A;
}

template<typename R, typename A, typename As...>
struct func_type<0, auto(A, As...)->R> {
  using return_t = R;
  using argument_t = A;
}

template<size_t I, typename R, typename A, typename As...>
struct func_type<I, auto(A, As...)->R> {}

};// namespace eop
