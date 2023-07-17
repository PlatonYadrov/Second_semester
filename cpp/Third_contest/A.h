#ifndef ITEROPS
#define ITEROPS
#include <iostream>

template <class Iterator>
void Advance(Iterator& iterator, int distans) {
  if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
                               std::random_access_iterator_tag>) {
    iterator += distans;
    return;
  }
  if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
                               std::bidirectional_iterator_tag>) {
    while (distans < 0) {
      ++distans;
      --iterator;
    }
  }
  while (distans > 0) {
    --distans;
    ++iterator;
  }
}

template <class Iterator>
Iterator Next(Iterator iterator, int distans) {
  Advance(iterator, distans);
  return iterator;
}

template <class Iterator>
Iterator Next(Iterator iterator) {
  return Next(iterator, 1);
}

template <class Iterator>
Iterator Prev(Iterator iterator, int distans) {
  Advance(iterator, -distans);
  return iterator;
}

template <class Iterator>
Iterator Prev(Iterator iterator) {
  return Prev(iterator, 1);
}

template <class Iterator>
int Distance(Iterator iterator_1, Iterator iterator_2) {
  if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
                               std::random_access_iterator_tag>) {
    return iterator_2 - iterator_1;
  }
  int distans = 0;
  while (iterator_1 != iterator_2) {
    ++distans;
    ++iterator_1;
  }
  return distans;
}

#endif
