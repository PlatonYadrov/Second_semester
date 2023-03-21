#include <cmath>
#include <iomanip>
#include <iostream>

class Point {
 public:
  int64_t x;
  int64_t y;
};

class Line {
 public:
  int64_t a;
  int64_t b;
  int64_t c;
};

std::istream& operator>>(std::istream& element, Line& line) {
  element >> line.a >> line.b >> line.c;
  return element;
}

class Vector {
 public:
  Vector() {
    x = 0;
    y = 0;
  }
  explicit Vector(const Line& l) {
    x = l.b;
    y = -l.a;
  }
  int64_t x;
  int64_t y;
};

std::ostream& operator<<(std::ostream& element, const Vector& vector) {
  element << vector.x << ' ' << vector.y;
  return element;
}

int main() {
  Line l_1;
  std::cin >> l_1;
  Line l_2;
  std::cin >> l_2;
  Vector v_1(l_1);
  Vector v_2(l_2);
  std::cout << std::fixed << std::setprecision(6);
  std::cout << v_1 << '\n';
  std::cout << v_2 << '\n';
  if (l_1.a * l_2.b == l_2.a * l_1.b) {
    if (l_1.a * l_2.b == 0) {
      std::cout << std::abs(l_1.c - l_2.c);
    } else if (l_1.c * l_2.b == l_2.c * l_1.b) {
      std::cout << 0.0;
    } else {
      int64_t sqr = std::pow(l_1.a, 2) * std::pow(l_2.b, 2) + std::pow(l_1.b, 2) * std::pow(l_2.b, 2);
      long double numerator = std::sqrt(sqr);
      std::cout << std::abs((l_1.c * l_2.b - l_2.c * l_1.b)) / numerator;
    }
  } else {
    long double denominator = l_2.b * l_1.a - l_1.b * l_2.a;
    std::cout << (l_2.c * l_1.b - l_1.c * l_2.b) / denominator << ' ';
    std::cout << (l_2.c * l_1.a - l_1.c * l_2.a) / -denominator;
  }
  return 0;
}
