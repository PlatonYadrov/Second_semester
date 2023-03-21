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
};

class Line {
 public:
  explicit Line(const Point& verifiable) {
    Point distant(1e5, verifiable.y + 1);
    a = verifiable.y - distant.y;
    b = distant.x - verifiable.x;
    c = verifiable.x * distant.y - distant.x * verifiable.y;
  }
  int64_t a;
  int64_t b;
  int64_t c;
};

std::istream& operator>>(std::istream& element, Point& point) {
  element >> point.x >> point.y;
  return element;
}

std::ostream& operator<<(std::ostream& element, const Point& point) {
  element << '(' << point.x << "; " << point.y << ')';
  return element;
}

bool operator==(const Point& a, const Point& b) {
  return ((a.x == b.x) && (a.y == b.y));
}

class Segment {
 public:
  Segment() {
    Point x(0, 0);
    Point y(1, 1);
    a = x;
    b = y;
  }
  Segment(const Point& a, const Point& b) {
    this->a = a;
    this->b = b;
  }
  Point a;
  Point b;
  Segment(const Segment& other) {
    a = other.a;
    b = other.b;
  }

  Segment& operator=(const Segment& other) = default;
};

class Vector {
 public:
  Vector() {
    x = 0;
    y = 0;
  }
  explicit Vector(const Line& line) {
    x = line.b;
    y = -line.a;
  }

  Vector(const Point& a, const Point& b) {
    x = b.x - a.x;
    y = b.y - a.y;
  }
  explicit Vector(const Segment& line_segment) {
    x = line_segment.b.x - line_segment.a.x;
    y = line_segment.b.y - line_segment.a.y;
  }
  int64_t x;
  int64_t y;
};

class Polygon {
 public:
  Polygon(const int& amount, const Segment* sides) {
    this->amount = amount;
    this->sides = new Segment[amount];
    for (int i = 0; i < amount; ++i) {
      this->sides[i] = sides[i];
    }
  }
  ~Polygon() {
    delete[] sides;
  }
  int amount;
  Segment* sides;
};

std::ostream& operator<<(std::ostream& element, const Polygon& poligon) {
  for (int i = 0; i < poligon.amount; ++i) {
    element << poligon.sides[i].a << ' ' << poligon.sides[i].b << '\n';
  }
  return element;
}

int64_t ScalarMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.x + v_1.y * v_2.y;
}

int64_t VectorMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

bool OnePointOnTheBorder(const Point& a, const Point& b, const Point& c) {
  if (a == c or b == c) {
    return true;
  }
  Vector vector_a_b(a, b);
  Vector vector_a_c(a, c);
  Vector vector_b_c(b, c);
  if (VectorMultiplication(vector_a_b, vector_a_c) == 0) {
    if (ScalarMultiplication(vector_a_b, vector_a_c) > 0) {
      if (ScalarMultiplication(vector_a_b, vector_b_c) < 0) {
        return true;
      }
    }
  }
  return false;
}

bool OnTheBorder(const Point& verifiable, const Polygon& my_poligon) {
  for (int i = 0; i < my_poligon.amount; ++i) {
    if (OnePointOnTheBorder(my_poligon.sides[i].a, my_poligon.sides[i].b, verifiable)) {
      return true;
    }
  }
  return false;
}

int64_t PointValue(const Line& line, const Point& point) {
  return line.a * point.x + line.b * point.y + line.c;
}

bool IntersectioLlineWithSegment(const Line& secant, const Segment& segment) {
  return PointValue(secant, segment.a) * PointValue(secant, segment.b) < 0;
}

bool Inside(const Point& verifiable, const Polygon& my_poligon) {
  if (OnTheBorder(verifiable, my_poligon)) {
    return true;
  }
  Line secant(verifiable);
  Vector v_secant(secant);
  int64_t count = 0;
  for (int i = 0; i < my_poligon.amount; ++i) {
    Segment present = my_poligon.sides[i];
    Vector v_a_o(present.a, verifiable);
    Vector v_a_b(present.a, present.b);
    if (IntersectioLlineWithSegment(secant, present)) {
      if (VectorMultiplication(v_a_o, v_a_b) * VectorMultiplication(v_secant, v_a_b) < 0) {
        ++count;
      }
    }
  }
  return count % 2;
}

int main() {
  int amount;
  std::cin >> amount;
  Point verifiable;
  std::cin >> verifiable;
  auto* sides = new Segment[amount];
  auto* vertex = new Point[amount];
  for (int i = 0; i < amount; ++i) {
    std::cin >> vertex[i];
  }
  for (int i = 0; i < amount; ++i) {
    if (i == amount - 1) {
      Segment temp(vertex[amount - 1], vertex[0]);
      sides[amount - 1] = temp;
    } else {
      Segment temp(vertex[i], vertex[i + 1]);
      sides[i] = temp;
    }
  }
  Polygon my_poligon(amount, sides);
  if (Inside(verifiable, my_poligon)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  delete[] sides;
  delete[] vertex;
  return 0;
}
