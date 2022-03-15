#include <iostream>
#include <concepts.hpp>
#include <concepts>

template<typename Domain, eop::Transformation<Domain> F, std::integral N>
constexpr auto power_unary(Domain x, N n, F f) -> Domain {
  while (n != N(0)) {
    n = n - N(1);
    x = f(x);
  }
  return x;
}

constexpr auto increment(int const num) -> int { return num + 1; }


int main() {}
