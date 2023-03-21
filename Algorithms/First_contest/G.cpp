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

class Polygon {
 public:
  Polygon(const int& amount, const Vector* sides) {
    this->amount = amount;
    this->sides = new Vector[amount];
    for (int i = 0; i < amount; ++i) {
      this->sides[i] = sides[i];
    }
  }
  ~Polygon() {
    delete[] sides;
  }
  int amount;
  Vector* sides;
};

std::ostream& operator<<(std::ostream& element, const Polygon& poligon) {
  for (int i = 0; i < poligon.amount; ++i) {
    element << poligon.sides[i].x << ' ' << poligon.sides[i].y << '\n';
  }
  return element;
}

int64_t VectorMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

bool ConvexityCheck(const Polygon& my_poligon) {
  auto* mults = new int64_t[my_poligon.amount];
  for (int i = 0; i < my_poligon.amount; ++i) {
    if (i == my_poligon.amount - 1) {
      mults[i] = VectorMultiplication(my_poligon.sides[i], my_poligon.sides[0]);
    } else {
      mults[i] = VectorMultiplication(my_poligon.sides[i], my_poligon.sides[i + 1]);
    }
  }
  int sign = 0;
  for (int i = 1; i < my_poligon.amount; ++i) {
    if (sign == 0 && mults[i] != 0) {
      sign = mults[i] / abs(mults[i]);
    }
    if (sign * mults[i] < 0) {
      delete[] mults;
      return false;
    }
  }
  delete[] mults;
  return true;
}

int main() {
  int amount;
  std::cin >> amount;
  auto* sides = new Vector[amount];
  auto* vertex = new Point[amount];
  for (int i = 0; i < amount; ++i) {
    std::cin >> vertex[i];
  }
  bool coinciding_vertex = false;
  for (int i = 0; i < amount - 1; ++i) {
    if (vertex[i] == vertex[i + 1]) {
      std::cout << "NO";
      coinciding_vertex = true;
      break;
    }
    Vector temp(vertex[i], vertex[i + 1]);
    sides[i] = temp;
  }
  if (!coinciding_vertex) {
    Vector temp(vertex[amount - 1], vertex[0]);
    sides[amount - 1] = temp;
    Polygon my_poligon(amount, sides);
    if (ConvexityCheck(my_poligon)) {
      std::cout << "YES";
    } else {
      std::cout << "NO";
    }
  }
  delete[] sides;
  delete[] vertex;
  return 0;
}
