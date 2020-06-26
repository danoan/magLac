#ifndef MAGLAC_CORE_BASE_RESOLVER_H
#define MAGLAC_CORE_BASE_RESOLVER_H

#include "SingleResolver.h"

namespace magLac {
namespace Core {
template<class TRange, bool= TRange::isFirst>
class Resolver {
};

template<class TRange>
class Resolver<TRange, true> {
 public:
  typedef std::vector<size_t> VectorOfHops;
  typedef Resolver<TRange, true> Self;

 public:
  Resolver(TRange &range) : range(range), previousSolver(*this) {};

  void set(const VectorOfHops &hops) { this->hops = hops; }

  template<typename TContainer>
  void operator>>(TContainer &container) {
    auto sr = Single::Resolver(range.begin(), hops);
    sr >> container;
  }

 public:
  TRange range;
  VectorOfHops hops;

  Self &previousSolver;
};

template<class TRange>
class Resolver<TRange, false> {
 public:
  typedef std::vector<size_t> VectorOfHops;

  typedef typename TRange::PreviousRange PreviousRange;
  typedef Resolver<PreviousRange, PreviousRange::isFirst> PreviousSolver;

 public:
  Resolver(TRange &range) : range(range),
                            previousSolver(PreviousSolver(range.previous)) {}

  void set(const VectorOfHops &hops) { this->hops = hops; }

  template<typename TContainer>
  PreviousSolver &operator>>(TContainer &container) {
    auto sr = Single::Resolver(range.begin(), hops);
    sr >> container;

    return previousSolver;
  }

 public:
  TRange range;
  VectorOfHops hops;

  PreviousSolver previousSolver;
};

}
}
#endif //MAGLAC_CORE_BASE_RESOLVER_H
