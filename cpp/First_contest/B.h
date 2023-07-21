#include <iostream>
#include <stdexcept>
#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <class T>
class UniquePtr {
 public:
  T* ptr_unique;
  UniquePtr() {
    ptr_unique = nullptr;
  }

  explicit UniquePtr(T* ptr) noexcept {
    ptr_unique = ptr;
  }

  ~UniquePtr() {
    delete ptr_unique;
  }

  UniquePtr(const UniquePtr& other) = delete;

  UniquePtr& operator=(const UniquePtr& other) = delete;

  UniquePtr(UniquePtr&& other) noexcept {
    ptr_unique = other.ptr_unique;
    other.ptr_unique = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (&other == this) {
      return *this;
    }
    delete ptr_unique;
    ptr_unique = other.ptr_unique;
    other.ptr_unique = nullptr;
    return *this;
  }

  T* Release() {
    auto* temp = ptr_unique;
    ptr_unique = nullptr;
    return temp;
  }

  void Reset(T* ptr = nullptr) {
    delete ptr_unique;
    ptr_unique = ptr;
  }

  void Swap(UniquePtr& other) {
    UniquePtr temp = std::move(other);
    other = std::move(*this);
    *this = std::move(temp);
  }

  T* Get() const {
    return ptr_unique;
  }

  T& operator*() const {
    return *ptr_unique;
  }

  T* operator->() const {
    return ptr_unique;
  }

  explicit operator bool() const {
    return ptr_unique;
  }
};

#endif
