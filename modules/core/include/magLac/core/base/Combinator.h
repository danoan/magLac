#ifndef MAGLAC_CORE_BASE_COMBINATOR_H
#define MAGLAC_CORE_BASE_COMBINATOR_H

#include <vector>

#include "magLac/core/base/Range.hpp"
#include "magLac/core/base/Event.h"
#include "magLac/core/base/FundamentalCombinator.h"

#include "Resolver.h"

namespace magLac {
namespace Core {
template<class TRange>
class Combinator {
 public:
  typedef TRange MyRange;
  typedef Resolver<MyRange, TRange::isFirst> MyResolver;
  typedef std::vector<FundamentalCombinator> FundamentalVector;

  typedef unsigned long int Size;

 private:
  typedef std::stack<Event> EventStack;

 public:
  Combinator(MyRange &range);

  bool next(MyResolver &resolver);

  MyResolver resolver();

 private:
  template<class TResolver>
  void setResolver(TResolver &resolver);

  template<class TResolver>
  void setResolver(TResolver &resolver, Size proxyVectorIndex);

 private:
  MyRange &range;
  FundamentalVector fv;

  Size numRanges;
  EventStack es;
};

template<class TRange>
void initializeFundamentalVector(std::vector<FundamentalCombinator> &fv, const TRange &range) {
  fv.push_back(FundamentalCombinator(range.length, range.elemsPerComb));
  if (TRange::isFirst) return;
  else initializeFundamentalVector(fv, range.previous);
}

template<class TRange>
Combinator<TRange> createCombinator(TRange &range) {
  return Combinator<TRange>(range);
}

#include "Combinator.hpp"
}
}

#endif//MAGLAC_CORE_BASE_COMBINATOR_H
