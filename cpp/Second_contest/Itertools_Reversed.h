#ifndef REVERSED_H
#define REVERSED_H
#define REVERSE_REVERSED_IMPLEMENTED
#define TEMPORARY_REVERSED_IMPLEMENTED

template <typename T>
class ReversedLvalue {
 public:
  T& object;
  explicit ReversedLvalue(T& obj) : object(obj) {
  }

  auto begin() const {  // NOLINT
    return object.rbegin();
  }

  auto end() const {  // NOLINT
    return object.rend();
  }

  auto rbegin() const {  // NOLINT
    return object.begin();
  }

  auto rend() const {  // NOLINT
    return object.end();
  }
};

template <typename T>
auto Reversed(T& obj) {
  return ReversedLvalue<T>(obj);
}

template <typename T>
class ReversedRvalue {
 public:
  T object;
  explicit ReversedRvalue(T&& obj) : object(std::move(obj)) {
  }

  auto begin() const {  // NOLINT
    return object.rbegin();
  }

  auto end() const {  // NOLINT
    return object.rend();
  }

  auto rbegin() const {  // NOLINT
    return object.begin();
  }

  auto rend() const {  // NOLINT
    return object.end();
  }
};

template <typename T>
auto Reversed(T&& obj) {
  return ReversedRvalue<T>(std::move(obj));
}
#endif
