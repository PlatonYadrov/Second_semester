#ifndef RANGE
#define RANGE
#define REVERSE_RANGE_IMPLEMENTED

class Iterator {
 public:
  int var;
  int step;

  Iterator() : var(0), step(1) {
  }

  Iterator(int value, int step_new) : var(value), step(step_new) {
  }

  int operator*() {
    return var;
  }

  Iterator operator++() {
    var += step;
    return *this;
  }

  bool operator!=(const Iterator& other) const {
    if (step == 0) {
      return false;
    }
    if (step > 0) {
      return other.var - var > 0;
    }
    return other.var - var < 0;
  }
};

class ReverseIterator {
 public:
  int var;
  int step;

  ReverseIterator() : var(0), step(1) {
  }

  ReverseIterator(int value, int step_new) : var(value), step(step_new) {
  }

  int operator*() {
    return var;
  }

  ReverseIterator operator++() {
    var -= step;
    return *this;
  }

  bool operator!=(const ReverseIterator& other) const {
    if (step == 0) {
      return false;
    }
    if (step > 0) {
      return other.var - var < 0;
    }
    return other.var - var > 0;
  }
};

class Configuration {
 private:
  Iterator begin_;
  Iterator end_;
  ReverseIterator rbegin_;
  ReverseIterator rend_;

 public:
  ReverseIterator FoundRBegin(int begin, int end, int step) {
    if ((step != 0) && ((end - begin) % step != 0)) {
      return ReverseIterator(begin + (end - begin + step - 1) / step * step - step, step);
    }
    return ReverseIterator(end - step, step);
  }

  Configuration(int begin, int end, int step, int amount) {
    if (amount == 1 && end > 0) {
      begin_ = Iterator(0, 1);
      end_ = Iterator(end, 1);
      rbegin_ = FoundRBegin(begin, end, step);
      rend_ = ReverseIterator(-1, 1);
    } else if (amount == 2 && end > begin) {
      begin_ = Iterator(begin, 1);
      end_ = Iterator(end, 1);
      rbegin_ = FoundRBegin(begin, end, step);
      rend_ = ReverseIterator(begin - 1, 1);
    } else if (amount == 3 && ((step > 0 && end > begin) || (step < 0 && end < begin))) {
      begin_ = Iterator(begin, step);
      end_ = Iterator(end, step);
      rbegin_ = FoundRBegin(begin, end, step);
      rend_ = ReverseIterator(begin - step, step);
    }
  }

  const Iterator begin() const {  // NOLINT
    return begin_;
  }

  const Iterator end() const {  // NOLINT
    return end_;
  }

  const ReverseIterator rbegin() const {  // NOLINT
    return rbegin_;
  }

  const ReverseIterator rend() const {  // NOLINT
    return rend_;
  }
};

Configuration inline Range(int end) {
  return Configuration(0, end, 1, 1);
}

Configuration inline Range(int begin, int end) {
  return Configuration(begin, end, 1, 2);
}

Configuration inline Range(int begin, int end, int step) {
  return Configuration(begin, end, step, 3);
}
#endif
