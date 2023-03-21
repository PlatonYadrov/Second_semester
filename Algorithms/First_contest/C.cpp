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

bool operator==(const Point& a, const Point& b) {
  return ((a.x == b.x) && (a.y == b.y));
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
};

int64_t ScalarMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.x + v_1.y * v_2.y;
}

int64_t VectorMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

bool OnLine(const Point& a, const Point& b, const Point& c) {
  if (a == c or b == c) {
    return true;
  }
  Vector vector_a_b(a, b);
  Vector vector_a_c(a, c);
  Vector vector_b_c(b, c);
  return VectorMultiplication(vector_a_b, vector_a_c) == 0;
}

bool OnRay(const Point& a, const Point& b, const Point& c) {
  if (!OnLine(a, b, c)) {
    return false;
  }
  Vector vector_a_b(a, b);
  Vector vector_a_c(a, c);
  Vector vector_b_c(b, c);
  return ScalarMultiplication(vector_a_b, vector_a_c) >= 0;
}

bool OnLineSegment(const Point& a, const Point& b, const Point& c) {
  if (!OnRay(a, b, c)) {
    return false;
  }
  Vector vector_a_b(a, b);
  Vector vector_a_c(a, c);
  Vector vector_b_c(b, c);
  return ScalarMultiplication(vector_a_b, vector_b_c) <= 0;
}

int main() {
  Point a;
  Point b;
  Point c;
  std::cin >> c >> a >> b;
  if (OnLine(a, b, c)) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
  if (OnRay(a, b, c)) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
  if (OnLineSegment(a, b, c)) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
  return 0;
}
