#ifndef STRING_H
#define STRING_H

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 public:
  size_t size_str;
  size_t capacity_str;
  char* string;
  String();
  String(size_t size, char symbol);
  String(const char* symbol);  // NOLINT
  String(const char* symbol, size_t size);
  String(char* symbol, size_t size);
  String(const String& other);
  String& operator=(const String& other);
  ~String();
  char& operator[](size_t i);
  const char& operator[](size_t i) const;
  char& At(size_t);
  const char& At(size_t i) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  char* CStr();
  const char* CStr() const;
  char* Data();
  const char* Data() const;
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String& other);
  void PopBack();
  void PushBack(const char symbol);
  String& operator+=(String other);
  void Resize(size_t new_size, const char symbol);
  void Reserve(size_t new_capacity);
  void ShrinkToFit();
};

String operator+(String other_1, String other_2);
bool operator<(String other_1, String other_2);
bool operator>=(String other_1, String other_2);
bool operator>(String other_1, String other_2);
bool operator<=(String other_1, String other_2);
bool operator==(String other_1, String other_2);
bool operator!=(String other_1, String other_2);
std::ostream& operator<<(std::ostream& element, const String& str);

#endif
