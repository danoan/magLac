#ifndef MAGLAC_CORE_BASE_RANGE_H
#define MAGLAC_CORE_BASE_RANGE_H

#include <algorithm>
#include <memory>

namespace magLac {
namespace Core {
template<typename TIteratorMaster, typename... TIterators>
struct Range {
  typedef TIteratorMaster IteratorType;

  typedef Range<TIteratorMaster, TIterators...> Self;

  Range(TIteratorMaster begin, TIteratorMaster end, size_t elemsPerComb)
      :m_begin(begin),
       m_end(end),
       elemsPerComb(elemsPerComb),
       length(std::distance(begin,end)) {}

  template<class TIteratorNext>
  auto addRange(TIteratorNext begin,
                TIteratorNext end, size_t elemsPerComb) const {
    return new Range<TIteratorNext, TIteratorMaster>(this, begin, end, elemsPerComb);
  }

  auto close(){
    return std::unique_ptr<Self>(this);
  }

  TIteratorMaster begin() const { return m_begin;}
  TIteratorMaster end() const { return m_end;}

 private:
  TIteratorMaster m_begin;
  TIteratorMaster m_end;

 public:
  size_t elemsPerComb;
  size_t length;

  Self* previous{nullptr};
  static const bool isFirst;
};

template<typename TIteratorMaster, typename TIteratorSecond, typename... TIterators>
struct Range<TIteratorMaster, TIteratorSecond, TIterators...> {
  typedef TIteratorMaster IteratorType;

  typedef Range<TIteratorMaster, TIteratorSecond, TIterators...> Self;
  typedef Range<TIteratorSecond, TIterators...> PreviousRange;

  Range(const PreviousRange* previous,
        TIteratorMaster begin, TIteratorMaster end, size_t elemsPerComb)
      :m_begin(begin),
       m_end(end),
       elemsPerComb(elemsPerComb),
       length(std::distance(begin,end)),
       previous(previous) {}

  ~Range(){ delete previous;}


  template<class TIteratorNext>
  auto addRange(TIteratorNext begin, TIteratorNext end, size_t elemsPerComb) const {
    return new Range<TIteratorNext, TIteratorMaster, TIteratorSecond, TIterators...>(this, begin, end, elemsPerComb);
  }

  auto close(){
    return std::unique_ptr<Self>(this);
  }

  TIteratorMaster begin() const { return m_begin;}
  TIteratorMaster end() const { return m_end;}

 private:
  TIteratorMaster m_begin;
  TIteratorMaster m_end;

 public:
  size_t elemsPerComb;
  size_t length;

  const PreviousRange* previous;
  static const bool isFirst;
};

template<typename TIterator>
Range<TIterator>* addRange(TIterator begin, TIterator end, unsigned long int elemsPerComb) {
  return new Range<TIterator>(begin, end, elemsPerComb);
}

template<typename TIteratorMaster, typename TIteratorSecond, typename... TIterators>
const bool Range<TIteratorMaster, TIteratorSecond, TIterators...>::isFirst = false;

template<typename TIteratorMaster, typename... TIterators>
const bool Range<TIteratorMaster, TIterators...>::isFirst = true;
}
}

#endif//MAGLAC_CORE_BASE_RANGE_H
