#include <algorithm>
#include <cmath>
#include <iostream>

class Point {
 public:
  Point() {
    x = 0;
    y = 0;
  }
  Point(const int64_t& x, const int64_t& y) {
    this->x = x;
    this->y = y;
  }
  int64_t x;
  int64_t y;
  Point(const Point& other) {
    x = other.x;
    y = other.y;
  }

  Point& operator=(const Point& other) = default;
};

std::istream& operator>>(std::istream& element, Point& point) {
  element >> point.x >> point.y;
  return element;
}

std::ostream& operator<<(std::ostream& element, const Point& point) {
  element << point.x << ' ' << point.y;
  return element;
}

bool operator==(Point a, Point b) {
  return ((a.x == b.x) && (a.y == b.y));
}

bool operator!=(Point a, Point b) {
  return ((a.x != b.x) || (a.y != b.y));
}

bool Comp(const Point& a, const Point& b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return a.y < b.y;
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
  Vector(const Vector& other) {
    x = other.x;
    y = other.y;
  }

  Vector& operator=(const Vector& other) = default;
};

int64_t VectorMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

bool operator<(Vector v_1, Vector v_2) {
  if (VectorMultiplication(v_1, v_2) != 0) {
    return (VectorMultiplication(v_1, v_2) < 0);
  }
  return v_1.x * v_1.x + v_1.y * v_1.y > v_2.x * v_2.x + v_2.y * v_2.y;
}

int ShellSearch(const int& amount, const Point* vertex, Point* answer) {
  Point point_now = vertex[0];
  int points_in_answer = 0;
  do {
    answer[points_in_answer] = point_now;
    ++points_in_answer;
    Point temp = vertex[0];
    for (int i = 0; i < amount; ++i) {
      Vector v_1(point_now, vertex[i]);
      Vector v_2(point_now, temp);
      if (v_1 < v_2) {
        temp = vertex[i];
      }
    }
    point_now = temp;
  } while (point_now != answer[0]);
  std::cout << points_in_answer << '\n';
  std::cout << answer[0] << '\n';
  for (int i = 1; i < points_in_answer; ++i) {
    std::cout << answer[i] << '\n';
  }
  return points_in_answer;
}

int64_t Area(const int& points, const Point* answer) {
  int64_t area = 0;
  for (int i = 0; i < points - 1; ++i) {
    area += answer[i + 1].x * answer[i].y - answer[i].x * answer[i + 1].y;
  }
  area += answer[0].x * answer[points - 1].y - answer[points - 1].x * answer[0].y;
  return std::abs(area);
}

int main() {
  int amount;
  std::cin >> amount;
  auto* vertex = new Point[amount];
  for (int i = 0; i < amount; ++i) {
    std::cin >> vertex[i];
  }
  std::sort(vertex, vertex + amount, Comp);
  auto* unique_vertex = new Point[amount];
  unique_vertex[0] = vertex[0];
  int new_amount = 1;
  for (int i = 1; i < amount; ++i) {
    if (unique_vertex[new_amount - 1] != vertex[i]) {
      unique_vertex[new_amount] = vertex[i];
      ++new_amount;
    }
  }
  auto* answer = new Point[new_amount];
  int points_in_answer = ShellSearch(new_amount, unique_vertex, answer);
  int64_t area = Area(points_in_answer, answer);
  if (area % 2 == 0) {
    std::cout << area / 2ll << '.' << 0;
  } else {
    std::cout << area / 2ll << '.' << 5;
  }
  delete[] vertex;
  delete[] unique_vertex;
  delete[] answer;
  return 0;
}
