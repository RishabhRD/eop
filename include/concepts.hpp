#include <concepts>

namespace eop {
template<typename Func, typename Domain>
concept TransformationValue = requires(Domain d, Func func) {
  { func(d) } -> std::same_as<Domain>;
};

template<typename Func, typename Domain>
concept TransformationRef = requires(Domain const &d, Func func) {
  { func(d) } -> std::same_as<Domain>;
};

template<typename Func, typename Domain>
concept Transformation =
  TransformationValue<Func, Domain> or TransformationRef<Func, Domain>;

template<typename Func, typename Domain>
concept Relation = requires(Domain const &d, Func func) {
  { func(d, d) } -> std::same_as<bool>;
};
}// namespace eop
