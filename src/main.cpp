#include <boost/ut.hpp>
#include <iostream>
#include <vector>
#include <stl.hpp>

using namespace boost::ut;

int main() {
  std::vector<int> vec{ 1, 2, 3, 4, 5 };
  stl::for_each(
    begin(vec), end(vec), [](auto num) { std::cout << num << std::endl; });
  expect(eq(stl::find(begin(vec), end(vec), 3) - begin(vec), 2));
  expect(
    eq(stl::find_if(begin(vec), end(vec), [](auto num) { return num == 3; })
         - begin(vec),
      2));
  expect(stl::any_of(begin(vec), end(vec), [](auto num) { return num == 3; }));
  expect(eq(
    stl::reduce(
      begin(vec), end(vec), 0, std::plus<int>{}, [](auto i) { return i + 1; }),
    20));
}
