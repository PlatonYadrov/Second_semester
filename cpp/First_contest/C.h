#include <stdexcept>
#include <iostream>

#ifndef SHAREDPTR_H
#define SHAREDPTR_H

template <class T>
class SharedPtr {
 public:
  T* ptr = nullptr;
  int* count = nullptr;

  SharedPtr() noexcept {
    ptr = nullptr;
    count = new int;
    *count = 1;
  }

  SharedPtr(T* other) noexcept {  // NOLINT
    ptr = other;
    count = new int;
    *count = 1;
  }

  ~SharedPtr() {
    if (count == nullptr) {
      return;
    }
    --(*count);
    if (*count == 0) {
      delete ptr;
      delete count;
      return;
    }
    ptr = nullptr;
    count = nullptr;
  }

  SharedPtr(const SharedPtr& other) noexcept {
    ptr = other.ptr;
    if (other.count == nullptr) {
      count = other.count;
    } else {
      ++(*other.count);
      count = other.count;
    }
  }

  SharedPtr<T>& operator=(const SharedPtr& other) {
    if (this == &other) {
      return *this;
    }
    if (*count == 1) {
      delete ptr;
      delete count;
    } else {
      --(*count);
    }
    ptr = other.ptr;
    if (other.count == nullptr) {
      count = other.count;
    } else {
      ++(*other.count);
      count = other.count;
    }
    return *this;
  }

  SharedPtr(SharedPtr<T>&& other) noexcept {
    ptr = other.ptr;
    other.ptr = nullptr;
    count = other.count;
    other.count = nullptr;
  }

  SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    if (*count == 1) {
      delete ptr;
      delete count;
      ptr = other.ptr;
      other.ptr = nullptr;
      count = other.count;
      other.count = nullptr;
      return *this;
    }
    --(*count);
    ptr = other.ptr;
    other.ptr = nullptr;
    count = other.count;
    other.count = nullptr;
    return *this;
  }

  void Reset(T* other = nullptr) {
    --(*count);
    if (*count == 0) {
      delete ptr;
      delete count;
    }
    count = new int;
    *count = 1;
    ptr = other;
  }

  void Swap(SharedPtr<T>& other) noexcept {
    int* temp_count = other.count;
    T* temp_ptr = other.ptr;
    other.count = count;
    count = temp_count;
    other.ptr = ptr;
    ptr = temp_ptr;
  }

  T* Get() const {
    return ptr;
  }

  int UseCount() const {
    if (ptr != nullptr) {
      return *count;
    }
    return 0;
  }

  T& operator*() const {
    return *ptr;
  }

  T* operator->() const {
    return ptr;
  }

  explicit operator bool() const {
    return ptr;
  }
};

#endif
