#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

template <class T>
class Vector {
 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  T* ptr_vector;
  size_t size_vector;
  size_t capacity_vector;
  Vector() {
    ptr_vector = nullptr;
    size_vector = 0;
    capacity_vector = 0;
  }

  explicit Vector(size_t size) {
    size_vector = size;
    capacity_vector = size;
    if (size == 0) {
      ptr_vector = nullptr;
    } else {
      ptr_vector = new T[size]{};
    }
  }

  Vector(size_t size, const T& var) {
    size_vector = size;
    capacity_vector = size;
    if (size_vector == 0) {
      ptr_vector = nullptr;
    } else {
      ptr_vector = new T[size];
      try {
        for (size_t i = 0; i < size; ++i) {
          ptr_vector[i] = var;
        }
      } catch (...) {
        delete[] ptr_vector;
        throw;
      }
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator begin, Iterator end) {
    size_vector = std::distance(begin, end);
    capacity_vector = size_vector;
    if (size_vector == 0) {
      ptr_vector = nullptr;
    } else {
      ptr_vector = new T[size_vector];
      try {
        for (size_t i = 0; i < size_vector; ++i) {
          ptr_vector[i] = *(begin + i);
        }
      } catch (...) {
        delete[] ptr_vector;
        throw;
      }
    }
  }

  Vector(std::initializer_list<T> initializer) : Vector(initializer.begin(), initializer.end()) {
  }

  Vector(const Vector& other) {
    size_vector = other.size_vector;
    capacity_vector = other.capacity_vector;
    if (size_vector == 0) {
      ptr_vector = nullptr;
      capacity_vector = 0;
    } else {
      ptr_vector = new T[other.capacity_vector];
      try {
        for (size_t i = 0; i < size_vector; ++i) {
          ptr_vector[i] = other.ptr_vector[i];
        }
      } catch (...) {
        delete[] ptr_vector;
        throw;
      }
    }
  }

  Vector(Vector&& other) noexcept {
    size_vector = other.size_vector;
    capacity_vector = other.capacity_vector;
    other.size_vector = 0;
    other.capacity_vector = 0;
    if (size_vector == 0) {
      capacity_vector = 0;
      ptr_vector = nullptr;
    } else {
      ptr_vector = other.ptr_vector;
    }
    other.ptr_vector = nullptr;
  }

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      if (capacity_vector < other.size_vector) {
        delete[] ptr_vector;
        try {
          ptr_vector = new T[other.size_vector];
        } catch (...) {
          size_vector = 0;
          capacity_vector = 0;
          ptr_vector = nullptr;
          throw;
        }
        capacity_vector = other.size_vector;
      }
      size_vector = other.size_vector;
      try {
        for (size_t i = 0; i < size_vector; ++i) {
          ptr_vector[i] = other.ptr_vector[i];
        }
      } catch (...) {
        size_vector = 0;
        throw;
      }
    }
    return *this;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      delete[] ptr_vector;
      size_vector = other.size_vector;
      other.size_vector = 0;
      ptr_vector = other.ptr_vector;
      other.ptr_vector = nullptr;
      capacity_vector = other.capacity_vector;
      other.capacity_vector = 0;
    }
    return *this;
  }

  ~Vector() {
    size_vector = 0;
    delete[] ptr_vector;
    capacity_vector = 0;
  }

  size_t Size() const noexcept {
    return size_vector;
  }

  bool Empty() const noexcept {
    return (size_vector == 0);
  }

  size_t Capacity() const noexcept {
    return capacity_vector;
  }

  T& operator[](size_t i) noexcept {
    return ptr_vector[i];
  }

  const T& operator[](size_t i) const noexcept {
    return ptr_vector[i];
  }

  T& At(size_t number) {
    if (number >= size_vector) {
      throw std::out_of_range("Out of range");
    }
    return ptr_vector[number];
  }

  const T& At(size_t number) const {
    if (number >= size_vector) {
      throw std::out_of_range("Out of range");
    }
    return ptr_vector[number];
  }

  T& Front() {
    return ptr_vector[0];
  }

  const T& Front() const {
    return ptr_vector[0];
  }

  T& Back() {
    return ptr_vector[size_vector - 1];
  }

  const T& Back() const {
    return ptr_vector[size_vector - 1];
  }

  T* Data() {
    return ptr_vector;
  }

  const T* Data() const {
    return ptr_vector;
  }

  void Swap(Vector& other) {
    Vector temp = std::move(other);
    other = std::move(*this);
    *this = std::move(temp);
  }

  void Resize(size_t size) {
    if (size <= capacity_vector) {
      size_vector = size;
      return;
    }
    auto* temp = new T[size]{};
    for (size_t i = 0; i < size_vector; ++i) {
      temp[i] = std::move(ptr_vector[i]);
    }
    delete[] ptr_vector;
    ptr_vector = temp;
    capacity_vector = size;
    size_vector = size;
  }

  void Resize(size_t size, const T& var) {
    if (size <= capacity_vector) {
      try {
        for (size_t i = size_vector; i < size; ++i) {
          ptr_vector[i] = var;
        }
      } catch (...) {
        for (size_t i = size_vector; i < size; ++i) {
          ptr_vector[i].~T();
        }
        throw;
      }
    } else {
      auto* temp = new T[size]{};
      try {
        for (size_t i = size_vector; i < size; ++i) {
          temp[i] = var;
        }
      } catch (...) {
        delete[] temp;
        throw;
      }
      for (size_t i = 0; i < size_vector; ++i) {
        temp[i] = std::move(ptr_vector[i]);
      }
      delete[] ptr_vector;
      ptr_vector = temp;
      capacity_vector = size;
    }
    size_vector = size;
  }

  void Reserve(size_t capacity) {
    if (capacity_vector < capacity) {
      auto* temp = new T[capacity];
      for (size_t i = 0; i < size_vector; ++i) {
        temp[i] = std::move(ptr_vector[i]);
      }
      delete[] ptr_vector;
      ptr_vector = temp;
    }
    capacity_vector = capacity;
  }

  void ShrinkToFit() {
    if (size_vector == 0) {
      delete[] ptr_vector;
      capacity_vector = 0;
      ptr_vector = nullptr;
    } else {
      auto* temp = new T[size_vector];
      for (size_t i = 0; i < size_vector; ++i) {
        temp[i] = std::move(ptr_vector[i]);
      }
      delete[] ptr_vector;
      capacity_vector = size_vector;
      ptr_vector = temp;
    }
  }

  void Clear() noexcept {
    size_vector = 0;
  }

  void PushBack(const T& var) {
    if (size_vector != capacity_vector) {
      try {
        ptr_vector[size_vector] = var;
      } catch (...) {
        ptr_vector[size_vector].~T();
        throw;
      }
      ++size_vector;
      return;
    }
    if (size_vector != 0) {
      auto* temp = new T[capacity_vector * 2];
      try {
        for (size_t i = 0; i <= size_vector; ++i) {
          if (i == size_vector) {
            temp[i] = var;
          } else {
            temp[i] = ptr_vector[i];
          }
        }
      } catch (...) {
        delete[] temp;
        throw;
      }
      delete[] ptr_vector;
      ptr_vector = temp;
      capacity_vector *= 2;
      ++size_vector;
    } else {
      auto* temp = new T[1];
      try {
        *temp = var;
      } catch (...) {
        delete[] temp;
        throw;
      }
      delete[] ptr_vector;
      ptr_vector = temp;
      ++size_vector;
      capacity_vector = size_vector;
    }
  }

  void PushBack(T&& var) {
    if (size_vector != capacity_vector) {
      ptr_vector[size_vector] = std::move(var);
      ++size_vector;
      return;
    }
    if (size_vector != 0) {
      auto* temp = new T[capacity_vector * 2];
      for (size_t i = 0; i <= size_vector; ++i) {
        if (i == size_vector) {
          temp[i] = std::move(var);
        } else {
          temp[i] = std::move(ptr_vector[i]);
        }
      }
      capacity_vector *= 2;
      ++size_vector;
      delete[] ptr_vector;
      ptr_vector = temp;
    } else {
      auto* temp = new T[1];
      *temp = std::move(var);
      delete[] ptr_vector;
      ptr_vector = temp;
      ++size_vector;
      capacity_vector = size_vector;
    }
  }

  void PopBack() noexcept {
    if (size_vector == 0) {
      return;
    }
    ptr_vector[size_vector - 1].~T();
    --size_vector;
  }

  ConstIterator begin() const {  // NOLINT
    return ptr_vector;
  }

  Iterator begin() {  // NOLINT
    return ptr_vector;
  }

  ConstIterator end() const {  // NOLINT
    return ptr_vector + size_vector;
  }

  Iterator end() {  // NOLINT
    return ptr_vector + size_vector;
  }

  ConstIterator cbegin() const {  // NOLINT
    return ptr_vector;
  }

  ConstIterator cend() const {  // NOLINT
    return ptr_vector + size_vector;
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return std::make_reverse_iterator(ptr_vector + size_vector);
  }

  ReverseIterator rbegin() {  // NOLINT
    return std::make_reverse_iterator(ptr_vector + size_vector);
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return std::make_reverse_iterator(ptr_vector + size_vector);
  }

  ConstReverseIterator rend() const {  // NOLINT
    return std::make_reverse_iterator(ptr_vector);
  }

  ReverseIterator rend() {  // NOLINT
    return std::make_reverse_iterator(ptr_vector);
  }

  ConstReverseIterator crend() const {  // NOLINT
    return std::make_reverse_iterator(ptr_vector);
  }
};

template <class T>
bool operator<(const Vector<T>& other_1, const Vector<T>& other_2) {
  size_t size_1 = other_1.size_vector;
  size_t size_2 = other_2.size_vector;
  if (size_1 < size_2) {
    for (size_t i = 0; i < size_1; ++i) {
      if (other_1.ptr_vector[i] != other_2.ptr_vector[i]) {
        return other_1.ptr_vector[i] < other_2.ptr_vector[i];
      }
    }
    return size_1 < size_2;
  }
  for (size_t i = 0; i < size_2; ++i) {
    if (other_1.ptr_vector[i] != other_2.ptr_vector[i]) {
      return other_1.ptr_vector[i] < other_2.ptr_vector[i];
    }
  }
  return size_1 < size_2;
}

template <class T>
bool operator>=(const Vector<T>& other_1, const Vector<T>& other_2) {
  return !(other_1 < other_2);
}

template <class T>
bool operator>(const Vector<T>& other_1, const Vector<T>& other_2) {
  size_t size_1 = other_1.size_vector;
  size_t size_2 = other_2.size_vector;
  if (size_1 < size_2) {
    for (size_t i = 0; i < size_1; ++i) {
      if (other_1.ptr_vector[i] != other_2.ptr_vector[i]) {
        return other_1.ptr_vector[i] > other_2.ptr_vector[i];
      }
    }
    return size_1 > size_2;
  }
  for (size_t i = 0; i < size_2; ++i) {
    if (other_1.ptr_vector[i] != other_2.ptr_vector[i]) {
      return other_1.ptr_vector[i] > other_2.ptr_vector[i];
    }
  }
  return size_1 > size_2;
}

template <class T>
bool operator<=(const Vector<T>& other_1, const Vector<T>& other_2) {
  return !(other_1 > other_2);
}

template <class T>
bool operator==(const Vector<T>& other_1, const Vector<T>& other_2) {
  size_t size_1 = other_1.size_vector;
  size_t size_2 = other_2.size_vector;
  if (size_1 != size_2) {
    return false;
  }
  for (size_t i = 0; i < size_1; ++i) {
    if (other_1.ptr_vector[i] != other_2.ptr_vector[i]) {
      return false;
    }
  }
  return true;
}

template <class T>
bool operator!=(const Vector<T>& other_1, const Vector<T>& other_2) {
  return !(other_1 == other_2);
}
#endif
