#include <cmath>
#include <iomanip>
#include <iostream>

class Point {
 public:
  int64_t x;
  int64_t y;
};

bool operator==(Point a, Point b) {
  return ((a.x == b.x) && (a.y == b.y));
}

class Vector {
 public:
  int64_t x;
  int64_t y;
};

Vector operator-(Vector v) {
  v.x = -v.x;
  v.y = -v.y;
  return v;
}

Vector CreateVector(const Point& a, const Point& b) {
  Vector vector_a_b;
  vector_a_b.x = b.x - a.x;
  vector_a_b.y = b.y - a.y;
  return vector_a_b;
}

int VectorMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

int ScalarMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.x + v_1.y * v_2.y;
}

bool BorderCheck(const Point& a_1, const Point& b_1, const Point& a_2, const Point& b_2) {
  Vector vector_a_1_a_2 = CreateVector(a_1, a_2);
  Vector vector_a_1_b_2 = CreateVector(a_1, b_2);
  Vector vector_b_1_a_2 = CreateVector(b_1, a_2);
  Vector vector_b_1_b_2 = CreateVector(b_1, b_2);
  if (ScalarMultiplication(vector_a_1_a_2, vector_a_1_b_2) <= 0) {
    return true;
  }
  if (ScalarMultiplication(vector_b_1_a_2, vector_b_1_b_2) <= 0) {
    return true;
  }
  if (ScalarMultiplication(-vector_a_1_a_2, -vector_b_1_a_2) <= 0) {
    return true;
  }
  if (ScalarMultiplication(-vector_a_1_b_2, -vector_b_1_b_2) <= 0) {
    return true;
  }
  return false;
}

bool Check(const Point& a_1, const Point& b_1, const Point& a_2, const Point& b_2) {
  if ((a_1 == a_2) || (a_1 == b_2) || (b_1 == a_2) || (b_1 == b_2)) {
    return true;
  }
  Vector vector_a_1_b_1 = CreateVector(a_1, b_1);
  Vector vector_a_2_b_2 = CreateVector(a_2, b_2);
  Vector vector_a_1_a_2 = CreateVector(a_1, a_2);
  Vector vector_a_1_b_2 = CreateVector(a_1, b_2);
  Vector vector_a_2_b_1 = CreateVector(a_2, b_1);
  int64_t mult_2_3 = VectorMultiplication(vector_a_2_b_2, -vector_a_1_a_2);
  int64_t mult_2_5 = VectorMultiplication(vector_a_2_b_2, vector_a_2_b_1);
  int64_t mult_1_3 = VectorMultiplication(vector_a_1_b_1, vector_a_1_a_2);
  int64_t mult_1_4 = VectorMultiplication(vector_a_1_b_1, vector_a_1_b_2);
  if (abs(mult_2_3) + abs(mult_2_5) + abs(mult_1_3) + abs(mult_1_4) == 0) {
    return BorderCheck(a_1, b_1, a_2, b_2);
  }
  return ((mult_2_3 * mult_2_5 <= 0) && (mult_1_3 * mult_1_4 <= 0));
}

double DistanceToLine(const Point& p_c, const Point& p_a, const Point& p_b) {
  int64_t coefficient_x = p_a.y - p_b.y;
  int64_t coefficient_y = p_b.x - p_a.x;
  int64_t free_coefficient = p_a.x * p_b.y - p_b.x * p_a.y;
  int64_t numerator = abs(coefficient_x * p_c.x + coefficient_y * p_c.y + free_coefficient);
  long double denominator = sqrt(std::pow(coefficient_x, 2) + std::pow(coefficient_y, 2));
  long double distance_to_line = numerator / denominator;
  return distance_to_line;
}

double Distance(const Point& a_1, const Point& b_1, const Point& a_2, const Point& b_2) {
  if (Check(a_1, b_1, a_2, b_2)) {
    return 0.0;
  }
  Vector vector_a_1_b_1 = CreateVector(a_1, b_1);
  Vector vector_a_2_b_2 = CreateVector(a_2, b_2);
  Vector vector_a_1_a_2 = CreateVector(a_1, a_2);
  Vector vector_a_1_b_2 = CreateVector(a_1, b_2);
  Vector vector_b_1_a_2 = CreateVector(b_1, a_2);
  Vector vector_b_1_b_2 = CreateVector(b_1, b_2);
  int64_t mult_1_3 = ScalarMultiplication(vector_a_1_b_1, vector_a_1_a_2);
  int64_t mult_1_4 = ScalarMultiplication(vector_a_1_b_1, vector_a_1_b_2);
  int64_t mult_1_5 = ScalarMultiplication(vector_a_1_b_1, vector_b_1_a_2);
  int64_t mult_1_6 = ScalarMultiplication(vector_a_1_b_1, vector_b_1_b_2);
  int64_t mult_2_3 = ScalarMultiplication(vector_a_2_b_2, -vector_a_1_a_2);
  int64_t mult_2_4 = ScalarMultiplication(vector_a_2_b_2, -vector_a_1_b_2);
  int64_t mult_2_5 = ScalarMultiplication(vector_a_2_b_2, -vector_b_1_a_2);
  int64_t mult_2_6 = ScalarMultiplication(vector_a_2_b_2, -vector_b_1_b_2);
  long double dist[8] = {10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000};
  if (mult_1_3 * mult_1_5 < 0) {
    dist[0] = DistanceToLine(a_2, a_1, b_1);
  }
  if (mult_1_4 * mult_1_6 < 0) {
    dist[1] = DistanceToLine(b_2, a_1, b_1);
  }
  if (mult_2_3 * mult_2_4 < 0) {
    dist[2] = DistanceToLine(a_1, a_2, b_2);
  }
  if (mult_2_5 * mult_2_6 < 0) {
    dist[3] = DistanceToLine(b_1, a_2, b_2);
  }
  dist[4] = sqrt(std::pow(a_1.x - a_2.x, 2) + std::pow(a_1.y - a_2.y, 2));
  dist[5] = sqrt(std::pow(b_1.x - b_2.x, 2) + std::pow(b_1.y - b_2.y, 2));
  dist[6] = sqrt(std::pow(a_1.x - b_2.x, 2) + std::pow(a_1.y - b_2.y, 2));
  dist[7] = sqrt(std::pow(b_1.x - a_2.x, 2) + std::pow(b_1.y - a_2.y, 2));
  long double min_1 = std::min(std::min(dist[0], dist[1]), std::min(dist[2], dist[3]));
  long double min_2 = std::min(std::min(dist[4], dist[5]), std::min(dist[6], dist[7]));
  long double min = std::min(min_1, min_2);
  return min;
}

int main() {
  Point a_1;
  Point b_1;
  Point a_2;
  Point b_2;
  std::cin >> a_1.x >> a_1.y >> b_1.x >> b_1.y;
  std::cin >> a_2.x >> a_2.y >> b_2.x >> b_2.y;
  std::cout << std::fixed << std::setprecision(6);
  std::cout << Distance(a_1, b_1, a_2, b_2);
  return 0;
}
