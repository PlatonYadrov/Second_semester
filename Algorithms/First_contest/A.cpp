#include <cmath>
#include <iomanip>
#include <iostream>

class Point {
 public:
  int64_t x;
  int64_t y;
};

std::istream& operator>>(std::istream& element, Point& point) {
  element >> point.x >> point.y;
  return element;
}

class Vector {
 public:
  Vector() {
    x = 0;
    y = 0;
  }
  Vector(const Point& a, const Point& b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
  int64_t x;
  int64_t y;
  long double Len() {
    return sqrt(x * x + y * y);
  }
};

std::ostream& operator<<(std::ostream& element, const Vector& vector) {
  element << vector.x << ' ' << vector.y;
  return element;
}

Vector operator+(const Vector& v_1, const Vector& v_2) {
  Vector v_sum;
  v_sum.x = v_1.x + v_2.x;
  v_sum.y = v_1.y + v_2.y;
  return v_sum;
}

int64_t ScalarMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.x + v_1.y * v_2.y;
}

int64_t VectorMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

double Area(const Vector& v_1, const Vector& v_2) {
  return abs(VectorMultiplication(v_1, v_2)) / 2.0;
}

int main() {
  Point start;
  Point finish;
  std::cin >> start >> finish;
  Vector v_1(start, finish);
  std::cin >> start >> finish;
  Vector v_2(start, finish);
  std::cout << std::fixed << std::setprecision(6) << v_1.Len() << ' ' << v_2.Len() << '\n';
  Vector v_sum = v_1 + v_2;
  std::cout << v_sum << '\n';
  std::cout << ScalarMultiplication(v_1, v_2) << ' ' << VectorMultiplication(v_1, v_2) << '\n';
  std::cout << Area(v_1, v_2);
  return 0;
}
