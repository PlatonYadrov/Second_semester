#include <iostream>
#include <string>
#ifndef OPTIONAL_H_
#define OPTIONAL_H_

class BadOptionalAccess : public std::exception {
 public:
  const char* what() const noexcept override {
    return "Bad Optional Access";
  }
};

template <class T>
class Optional {
 public:
  bool has_value = false;
  char memory[sizeof(T)];
  T& Object() {
    return *reinterpret_cast<T*>(memory);
  }
  const T& Object() const {
    return *reinterpret_cast<const T*>(memory);
  }

  Optional() {
    has_value = false;
  }

  Optional(const T& obj) {  // NOLINT
    has_value = true;
    new (memory) T(obj);
  }

  Optional(T&& obj) {  // NOLINT
    has_value = true;
    new (memory) T(std::move(obj));
  }

  Optional(const Optional& other) {
    has_value = other.has_value;
    if (has_value) {
      new (memory) T(other.Object());
    }
  }

  Optional(Optional&& other) noexcept {
    has_value = other.has_value;
    if (has_value) {
      new (memory) T(std::move(other.Object()));
    }
  }

  Optional& operator=(const T& other) {
    if (has_value) {
      Object() = other;
      return *this;
    }
    has_value = true;
    new (memory) T(other);
    return *this;
  }

  Optional& operator=(T&& other) {
    if (has_value) {
      Object() = std::move(other);
      return *this;
    }
    has_value = true;
    new (memory) T(std::move(other));
    return *this;
  }

  Optional& operator=(const Optional& other) {
    if (this == &other) {
      return *this;
    }
    if (other.has_value && has_value) {
      Object() = other.Object();
    }
    if (other.has_value && !has_value) {
      has_value = true;
      new (memory) T(*reinterpret_cast<const T*>(other.memory));
    }
    if (!other.has_value && has_value) {
      Object().~T();
      has_value = false;
    }
    return *this;
  }

  Optional& operator=(Optional&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    if (other.has_value && has_value) {
      Object() = std::move(other.Object());
    }
    if (other.has_value && !has_value) {
      has_value = true;
      new (memory) T(std::move(other.Object()));
    }
    if (!other.has_value && has_value) {
      Object().~T();
      has_value = false;
    }
    return *this;
  }

  ~Optional() {
    if (!has_value) {
      return;
    }
    Object().~T();
    has_value = false;
  }

  bool HasValue() const noexcept {
    return has_value;
  }

  explicit operator bool() const noexcept {
    return has_value;
  }

  T& Value() {
    if (!has_value) {
      throw BadOptionalAccess{};
    }
    return Object();
  }

  const T& Value() const {
    if (!has_value) {
      throw BadOptionalAccess{};
    }
    return Object();
  }

  T& operator*() {
    return Object();
  }

  const T& operator*() const {
    return Object();
  }

  template <class... Arguments>
  T& Emplace(Arguments&&... arguments) {
    if (!has_value) {
      has_value = true;
      return *(new (memory) T(std::forward<Arguments>(arguments)...));
    }
    Object().~T();
    return *(new (memory) T(std::forward<Arguments>(arguments)...));
  }

  void Reset() {
    if (!has_value) {
      return;
    }
    Object().~T();
    has_value = false;
  }

  void Swap(Optional& other) {
    std::swap(*this, other);
  }
};
#endif
