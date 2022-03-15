#include "concepts.hpp"

template<typename Domain, eop::Relation<Domain> Comparator>
Domain const &select_2_4_ab_cd(Domain const &a,
  Domain const &b,
  Domain const &c,
  Domain const &d,
  Comparator cmp) {
  if (cmp(d, b)) {
    return select_1_2(a, d);
  } else {
    return select_1_2(b, c);
  }
}

template<typename Domain, eop::Relation<Domain> Comparator>
Domain const &select_2_4_ab(Domain const &a,
  Domain const &b,
  Domain const &c,
  Domain const &d,
  Comparator cmp) {
  if (cmp(d, c)) {
    return select_2_4_ab_cd(a, b, d, c);
  } else {
    return select_2_4_ab_cd(a, b, c, d);
  }
}

template<typename Domain, eop::Relation<Domain> Comparator>
Domain const &select_2_4(Domain const &a,
  Domain const &b,
  Domain const &c,
  Domain const &d,
  Comparator cmp) {
  if (cmp(b, a)) {
    return select_2_4_ab(b, a, c, d);
  } else {
    return select_2_4_ab(a, b, c, d);
  }
}
