#include <iostream>
#include <stdexcept>
#include "cppstring.h"

String::String() {
  string = nullptr;
  size_str = 0;
  capacity_str = 0;
}

String::String(size_t size, const char symbol) {
  size_str = size;
  capacity_str = size;
  if (size == 0) {
    string = nullptr;
  } else {
    string = new char[size + 1];
    for (size_t i = 0; i <= size; ++i) {
      if (i != size) {
        string[i] = symbol;
      } else {
        string[size] = '\0';
      }
    }
  }
}

String::String(const char* symbol) {
  if (symbol[0] == '\0') {
    string = nullptr;
    size_str = 0;
    capacity_str = 0;
  } else {
    size_str = 0;
    do {
      ++size_str;
    } while (symbol[size_str] != '\0');
    capacity_str = size_str;
    string = new char[size_str + 1];
    for (size_t i = 0; i < size_str; ++i) {
      string[i] = symbol[i];
    }
  }
}

String::String(const char* symbol, size_t size) {
  size_str = size;
  capacity_str = size_str;
  if (size == 0) {
    string = nullptr;
  } else {
    string = new char[size_str + 1];
    for (size_t i = 0; i <= size; ++i) {
      if (i != size) {
        string[i] = symbol[i];
      } else {
        string[i] = '\0';
      }
    }
  }
}

String::String(const String& other) {
  size_str = other.size_str;
  capacity_str = other.capacity_str;
  if (size_str == 0) {
    string = nullptr;
  } else {
    string = new char[capacity_str + 1];
    for (size_t i = 0; i <= size_str; ++i) {
      if (i == size_str) {
        string[i] = '\0';
      } else {
        string[i] = other.string[i];
      }
    }
  }
}

String& String::operator=(const String& other) {
  if (this == &other) {
    return *this;
  }
  delete[] string;
  size_str = other.size_str;
  capacity_str = other.capacity_str;
  if (size_str == 0) {
    string = nullptr;
  } else {
    string = new char[capacity_str + 1];
    for (size_t i = 0; i <= size_str; ++i) {
      if (i != size_str) {
        string[i] = other.string[i];
      } else {
        string[i] = '\0';
      }
    }
  }
  return *this;
}

String::~String() {
  size_str = 0;
  capacity_str = 0;
  delete[] string;
}

char& String::operator[](size_t i) {
  return string[i];
}

const char& String::operator[](size_t i) const {
  return string[i];
}

char& String::At(size_t i) {
  if (i < size_str) {
    return string[i];
  }
  throw StringOutOfRange{};
}

const char& String::At(size_t i) const {
  if (i < size_str) {
    return string[i];
  }
  throw StringOutOfRange{};
}

char& String::Front() {
  return string[0];
}

const char& String::Front() const {
  return string[0];
}

char& String::Back() {
  return string[size_str - 1];
}

const char& String::Back() const {
  return string[size_str - 1];
}

char* String::CStr() {
  return string;
}

const char* String::CStr() const {
  return string;
}

char* String::Data() {
  return string;
}

const char* String::Data() const {
  return string;
}

bool String::Empty() const {
  return !(size_str > 0);
}

size_t String::Size() const {
  return size_str;
}

size_t String::Length() const {
  return size_str;
}

size_t String::Capacity() const {
  return capacity_str;
}

void String::Clear() {
  size_str = 0;
}

void String::Swap(String& other) {
  String temp = std::move(other);
  other = std::move(*this);
  *this = std::move(temp);
}

void String::PopBack() {
  --size_str;
}

void String::PushBack(const char symbol) {
  if (size_str == capacity_str) {
    if (capacity_str != 0) {
      capacity_str *= 2;
    } else {
      capacity_str += 1;
    }
    char* temp = string;
    string = new char[capacity_str + 1];
    for (size_t i = 0; i < size_str; ++i) {
      string[i] = temp[i];
    }
    delete[] temp;
  }
  string[size_str] = symbol;
  string[size_str + 1] = '\0';
  ++size_str;
}

String& String::operator+=(String other) {
  size_t size_other = other.size_str;
  for (size_t i = 0; i < size_other; ++i) {
    PushBack(other.string[i]);
  }
  return *this;
}

void String::Resize(size_t new_size, const char symbol) {
  if (new_size <= size_str) {
    string[new_size] = '\0';
    size_str = new_size;
  } else {
    for (size_t i = size_str; i < new_size; ++i) {
      PushBack(symbol);
    }
  }
}

void String::Reserve(size_t new_capacity) {
  if (new_capacity > capacity_str) {
    capacity_str = new_capacity;
    char* temp = string;
    string = new char[new_capacity + 1];
    for (size_t i = 0; i <= size_str; ++i) {
      if (i != size_str) {
        string[i] = temp[i];
      } else {
        string[size_str] = '\0';
        delete[] temp;
      }
    }
  }
}

void String::ShrinkToFit() {
  if (capacity_str > size_str) {
    capacity_str = size_str;
    char* temp = string;
    string = new char[size_str + 1];
    for (size_t i = 0; i <= size_str; ++i) {
      if (i != size_str) {
        string[i] = temp[i];
      } else {
        string[i] = '\0';
        delete[] temp;
      }
    }
  }
}

String operator+(String other_1, String other_2) {
  size_t size_other = other_2.size_str;
  for (size_t i = 0; i < size_other; ++i) {
    other_1.PushBack(other_2.string[i]);
  }
  return other_1;
}

bool operator<(String other_1, String other_2) {
  size_t size_1 = other_1.size_str;
  size_t size_2 = other_2.size_str;
  if (size_1 < size_2) {
    for (size_t i = 0; i < size_1; ++i) {
      if (other_1.string[i] != other_2.string[i]) {
        return other_1.string[i] < other_2.string[i];
      }
    }
    return size_1 < size_2;
  }
  for (size_t i = 0; i < size_2; ++i) {
    if (other_1.string[i] != other_2.string[i]) {
      return other_1.string[i] < other_2.string[i];
    }
  }
  return size_1 < size_2;
}

bool operator>=(String other_1, String other_2) {
  return !(other_1 < other_2);
}

bool operator>(String other_1, String other_2) {
  size_t size_1 = other_1.size_str;
  size_t size_2 = other_2.size_str;
  if (size_1 < size_2) {
    for (size_t i = 0; i < size_1; ++i) {
      if (other_1.string[i] != other_2.string[i]) {
        return other_1.string[i] > other_2.string[i];
      }
    }
    return size_1 > size_2;
  }
  for (size_t i = 0; i < size_2; ++i) {
    if (other_1.string[i] != other_2.string[i]) {
      return other_1.string[i] > other_2.string[i];
    }
  }
  return size_1 > size_2;
}

bool operator<=(String other_1, String other_2) {
  return !(other_1 > other_2);
}

bool operator==(String other_1, String other_2) {
  size_t size_1 = other_1.size_str;
  size_t size_2 = other_2.size_str;
  if (size_1 != size_2) {
    return false;
  }
  for (size_t i = 0; i < size_1; ++i) {
    if (other_1.string[i] != other_2.string[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(String other_1, String other_2) {
  return !(other_1 == other_2);
}

std::ostream& operator<<(std::ostream& element, const String& str) {
  for (size_t i = 0; i < str.size_str; ++i) {
    element << str.string[i];
  }
  return element;
}
