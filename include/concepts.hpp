#include <concepts>

namespace eop {
template<typename Func, typename Domain>
concept transformation = requires(Domain d, Func func) {
  { func(d) } -> std::same_as<Domain>;
};

template<typename Func, typename Domain>
concept predicate = requires(Domain domain, Func func) {
  { func(domain) } -> std::same_as<bool>;
};

template<typename Func, typename Domain>
concept relation = requires(Domain const &d, Func func) {
  { func(d, d) } -> std::same_as<bool>;
};

template<typename Func, typename... Domain>
concept callable_with = requires(Func func, Domain... domain) {
  func(domain...);
};
}// namespace eop
