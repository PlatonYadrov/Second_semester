#include <cmath>
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

Vector operator-(Vector v) {
  v.x = -v.x;
  v.y = -v.y;
  return v;
}

int64_t VectorMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

int64_t ScalarMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.x + v_1.y * v_2.y;
}

bool OnTheBorder(const Point& a_1, const Point& b_1, const Point& a_2, const Point& b_2) {
  Vector vector_a_1_a_2(a_1, a_2);
  Vector vector_a_1_b_2(a_1, b_2);
  Vector vector_b_1_a_2(b_1, a_2);
  Vector vector_b_1_b_2(b_1, b_2);
  if (ScalarMultiplication(vector_a_1_a_2, vector_a_1_b_2) <= 0) {
    return true;
  }
  if (ScalarMultiplication(vector_b_1_a_2, vector_b_1_b_2) <= 0) {
    return true;
  }
  if (ScalarMultiplication(-vector_a_1_a_2, -vector_b_1_a_2) <= 0) {
    return true;
  }
  return ScalarMultiplication(-vector_a_1_b_2, -vector_b_1_b_2) <= 0;
}

bool Intersection(const Point& a_1, const Point& b_1, const Point& a_2, const Point& b_2) {
  if ((a_1 == a_2) || (a_1 == b_2) || (b_1 == a_2) || (b_1 == b_2)) {
    return true;
  }
  Vector vector_a_1_b_1(a_1, b_1);  // 1
  Vector vector_a_2_b_2(a_2, b_2);  // 2
  Vector vector_a_1_a_2(a_1, a_2);  // 3
  Vector vector_a_1_b_2(a_1, b_2);  // 4
  Vector vector_a_2_b_1(a_2, b_1);  // 5
  int64_t mult_2_3 = VectorMultiplication(vector_a_2_b_2, -vector_a_1_a_2);
  int64_t mult_2_5 = VectorMultiplication(vector_a_2_b_2, vector_a_2_b_1);
  int64_t mult_1_3 = VectorMultiplication(vector_a_1_b_1, vector_a_1_a_2);
  int64_t mult_1_4 = VectorMultiplication(vector_a_1_b_1, vector_a_1_b_2);
  if (std::abs(mult_2_3) + std::abs(mult_2_5) + std::abs(mult_1_3) + std::abs(mult_1_4) == 0) {
    return OnTheBorder(a_1, b_1, a_2, b_2);
  }
  return ((mult_2_3 * mult_2_5 <= 0) && (mult_1_3 * mult_1_4 <= 0));
}

int main() {
  Point a_1;
  Point b_1;
  Point a_2;
  Point b_2;
  std::cin >> a_1 >> b_1 >> a_2 >> b_2;
  if (Intersection(a_1, b_1, a_2, b_2)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
