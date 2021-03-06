#include "magLac/lab/test/core/multiple/combinator/correcteness.h"

namespace std {
template<>
struct hash<magLac::Test::MultipleCombinator::Element> {
  std::size_t operator()(const magLac::Test::MultipleCombinator::Element &e) const noexcept {
    return std::hash<int>{}(e.e1[0]) + std::hash<std::string>{}(e.e2[0]);
  }

};

}

namespace magLac {
namespace Test {
namespace MultipleCombinator {
CombinationSet expectedCS() {
  CombinationSet cs;
  cs.insert(Element({1, 2}, {"Glasses"}));
  cs.insert(Element({1, 2}, {"Cards"}));
  cs.insert(Element({1, 3}, {"Cards"}));
  cs.insert(Element({1, 3}, {"Glasses"}));
  cs.insert(Element({2, 3}, {"Cards"}));
  cs.insert(Element({2, 3}, {"Glasses"}));

  return cs;
}

bool correcteness(Logger &logger) {
  using namespace magLac::Core;

  logger << Logger::HeaderTwo << "Test Correcteness" << Logger::Normal;

  auto combExplorer = takeFromEach({2, 1}, {1, 2, 3}, {"Glasses", "Cards"});

  IntVector c1(2);
  StringVector c2(1);
  std::vector<Element> combinationSet;
  while (combExplorer.next(c1, c2)) {
    combinationSet.push_back(Element(c1, c2));
  }

  bool flag = true;
  CombinationSet checkCS = expectedCS();
  for (auto it = combinationSet.begin(); it != combinationSet.end(); ++it) {
    if (checkCS.find(*it) == checkCS.end()) {
      flag = false;
      break;
    }
  }

  for (auto x:combinationSet) std::cout << x << "\n";

  flag = flag && checkCS.size() == combinationSet.size();

  logger << "Passed: " << flag;
  return flag;
}

std::ostream &operator<<(std::ostream &os, const Element &e) {
  for (auto x: e.e1) os << x << ",";
  for (auto x: e.e2) os << x << ",";

  return os;
}

}
}
}