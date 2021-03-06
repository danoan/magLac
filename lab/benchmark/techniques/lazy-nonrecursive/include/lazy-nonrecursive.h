#ifndef MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_H
#define MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_H

#include <stack>
#include <vector>

#include "Event.h"

namespace magLac {
namespace LazyNonRecursive {
template<class TElementType, class TElementIterator>
class LazyCombinator {
 public:
  typedef std::vector<TElementType> CombinationSequence;

 private:
  typedef std::stack<Event> EventStack;

 private:
  inline TElementIterator moveIt(TElementIterator it, size_t steps) const {
    for (; steps > 0; --steps) ++it;
    return it;
  }

 public:
  LazyCombinator(size_t combSize, TElementIterator begin, TElementIterator end);
  bool next(CombinationSequence &nextComb);

 private:
  EventStack es;
  CombinationSequence currComb;

  size_t combSize;
  TElementIterator begin, end;
};

template<class TElementIterator, class TElementType=typename TElementIterator::value_type>
LazyCombinator<TElementType, TElementIterator> combinations(unsigned long int combSize,
                                                            TElementIterator begin,
                                                            TElementIterator end) {
  return LazyCombinator<TElementType, TElementIterator>(combSize, begin, end);
}
}
}

#include "lazy-nonrecursive.hpp"

#endif //MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_H
