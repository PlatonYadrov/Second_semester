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
};

int64_t ScalarMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.x + v_1.y * v_2.y;
}

long double DistanceToLine(const Point& a, const Point& b, const Point& c) {
  Vector vector_a_b(a, b);
  Vector vector_a_c(a, c);
  Vector vector_b_c(b, c);
  int64_t coefficient_x = a.y - b.y;
  int64_t coefficient_y = b.x - a.x;
  int64_t free_coefficient = a.x * b.y - b.x * a.y;
  int64_t numerator = std::abs(coefficient_x * c.x + coefficient_y * c.y + free_coefficient);
  long double denominator = std::sqrt(std::pow(coefficient_x, 2) + std::pow(coefficient_y, 2));
  long double distance_to_line = numerator / denominator;
  return distance_to_line;
}

long double DistanceToRay(const Point& a, const Point& b, const Point& c) {
  Vector vector_a_b(a, b);
  Vector vector_a_c(a, c);
  Vector vector_b_c(b, c);
  long double distance_a_c = std::sqrt(std::pow(a.x - c.x, 2) + std::pow(a.y - c.y, 2));
  long double distance_to_ray;
  if (ScalarMultiplication(vector_a_b, vector_a_c) > 0) {
    distance_to_ray = DistanceToLine(a, b, c);
  } else {
    distance_to_ray = distance_a_c;
  }
  return distance_to_ray;
}

long double DistanceToLineSegment(const Point& a, const Point& b, const Point& c) {
  Vector vector_a_b(a, b);
  Vector vector_a_c(a, c);
  Vector vector_b_c(b, c);
  long double distance_a_c = std::sqrt(std::pow(a.x - c.x, 2) + std::pow(a.y - c.y, 2));
  long double distance_b_c = std::sqrt(std::pow(b.x - c.x, 2) + std::pow(b.y - c.y, 2));
  long double distance_to_line_segmeit;
  if (ScalarMultiplication(vector_a_b, vector_a_c) > 0) {
    if (ScalarMultiplication(vector_a_b, vector_b_c) < 0) {
      distance_to_line_segmeit = DistanceToLine(a, b, c);
    } else {
      distance_to_line_segmeit = distance_b_c;
    }
  } else {
    distance_to_line_segmeit = distance_a_c;
  }
  return distance_to_line_segmeit;
}

int main() {
  Point a;
  Point b;
  Point c;
  std::cin >> c >> a >> b;
  std::cout << std::fixed << std::setprecision(6);
  std::cout << DistanceToLine(a, b, c) << '\n';
  std::cout << DistanceToRay(a, b, c) << '\n';
  std::cout << DistanceToLineSegment(a, b, c) << '\n';
  return 0;
}
