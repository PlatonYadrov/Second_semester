#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

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

class PointInZone {
 public:
  PointInZone() {
    Point p(0, 0);
    point = p;
    zone = 0;
  }
  PointInZone(Point p, int nomber) {
    point = p;
    zone = nomber;
  }
  Point point;
  int zone;
  PointInZone(const PointInZone& other) {
    point = other.point;
    zone = other.zone;
  }

  PointInZone& operator=(const PointInZone& other) = default;
};

class Line {
 public:
  explicit Line(const Point& verifiable) {
    Point distant(1, verifiable.y + 1);
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

std::istream& operator>>(std::istream& element, PointInZone& point) {
  element >> point.point;
  return element;
}

std::ostream& operator<<(std::ostream& element, const PointInZone& point) {
  element << point.zone;
  return element;
}

bool operator==(Point a, Point b) {
  return ((a.x == b.x) && (a.y == b.y));
}

bool operator!=(Point a, Point b) {
  return ((a.x != b.x) || (a.y != b.y));
}

Point operator-(Point a, Point b) {
  Point temp;
  temp.x = a.x - b.x;
  temp.y = a.y - b.y;
  return temp;
}

Point operator+(Point a, Point b) {
  Point temp;
  temp.x = a.x + b.x;
  temp.y = a.y + b.y;
  return temp;
}

class LineSegment {
 public:
  LineSegment() {
    Point x(0, 0);
    Point y(1, 1);
    a = x;
    b = y;
  }
  LineSegment(const Point& a, const Point& b) {
    this->a = a;
    this->b = b;
  }
  Point a;
  Point b;
  LineSegment(const LineSegment& other) {
    a = other.a;
    b = other.b;
  }

  LineSegment& operator=(const LineSegment& other) = default;
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

  explicit Vector(const LineSegment& line_segment) {
    x = line_segment.b.x - line_segment.a.x;
    y = line_segment.b.y - line_segment.a.y;
  }
  int64_t x;
  int64_t y;
  Vector(const Vector& other) {
    x = other.x;
    y = other.y;
  }

  Vector& operator=(const Vector& other) = default;
};

Vector operator-(Vector v) {
  v.x = -v.x;
  v.y = -v.y;
  return v;
}

class Polygon {
 public:
  Polygon() {
    LineSegment p;
    this->amount = 1;
    this->sides.push_back(p);
  }
  Polygon(int& amount, LineSegment* sides) {
    this->amount = amount;
    for (int i = 0; i < amount; ++i) {
      this->sides.push_back(sides[i]);
    }
  }
  Polygon(int& amount, std::vector<Point> vertex) {
    this->amount = amount;
    for (int i = 0; i < amount; ++i) {
      if (i != amount - 1) {
        LineSegment seg(vertex[i], vertex[i + 1]);
        this->sides.push_back(seg);
      } else {
        LineSegment seg(vertex[i], vertex[0]);
        this->sides.push_back(seg);
      }
    }
  }
  int amount;
  std::vector<LineSegment> sides;
  Polygon(const Polygon& other) {
    this->amount = other.amount;
    for (int i = 0; i < amount; ++i) {
      this->sides.push_back(other.sides[i]);
    }
  }

  Polygon& operator=(const Polygon& other) = default;
};

std::ostream& operator<<(std::ostream& element, const Polygon& poligon) {
  for (int i = 0; i < poligon.amount; ++i) {
    element << poligon.sides[i].a << ' ' << poligon.sides[i].b << '\n';
  }
  return element;
}

int64_t ScalarMultiplication(Vector v_1, Vector v_2) {
  return v_1.x * v_2.x + v_1.y * v_2.y;
}

int64_t VectorMultiplication(const Vector& v_1, const Vector& v_2) {
  return v_1.x * v_2.y - v_2.x * v_1.y;
}

bool operator<(const Point& p_1, const Point& p_2) {
  Point p_0(0, 0);
  Vector v_1(p_0, p_1);
  Vector v_2(p_0, p_2);
  if (VectorMultiplication(v_1, v_2) != 0) {
    return (VectorMultiplication(v_1, v_2) > 0);
  }
  return v_1.x * v_1.x + v_1.y * v_1.y < v_2.x * v_2.x + v_2.y * v_2.y;
}

void FirstPoint(const int& amount, std::vector<Point>& vertex) {
  for (int i = 1; i < amount; ++i) {
    if (vertex[i].x < vertex[0].x || ((vertex[i].x == vertex[0].x) && (vertex[i].y < vertex[0].y))) {
      std::swap(vertex[0], vertex[i]);
    }
  }
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

Polygon ShellSearch(int& amount, std::vector<Point>& vertex) {
  std::vector<Point> answer(amount);
  answer[0] = vertex[0];
  answer[1] = vertex[1];
  int points_in_answer = 2;
  for (int i = 2; i < amount; ++i) {
    while (points_in_answer >= 2) {
      int id = points_in_answer - 1;
      Vector v_1(answer[id - 1], answer[id]);
      Vector v_2(answer[id], vertex[i]);
      if (VectorMultiplication(v_1, v_2) <= 0) {
        --points_in_answer;
      } else {
        break;
      }
    }
    answer[points_in_answer] = vertex[i];
    ++points_in_answer;
  }
  Polygon temp(points_in_answer, answer);
  std::vector<int> numbers(amount);
  int all_numbers = 0;
  for (int i = 0; i < amount; ++i) {
    if (OnTheBorder(vertex[i], temp)) {
      numbers[all_numbers] = i;
      ++all_numbers;
    }
  }
  std::vector<Point> temp_arr(amount - all_numbers);
  all_numbers = 0;
  for (int i = 0; i < amount; ++i) {
    if (i != numbers[all_numbers]) {
      temp_arr[i - all_numbers] = vertex[i];
    } else {
      ++all_numbers;
    }
  }
  for (int i = 0; i < amount - all_numbers; ++i) {
    vertex[i] = temp_arr[i];
  }
  amount -= all_numbers;
  return temp;
}

bool BorderCheck(const Point& a_1, const Point& b_1, const Point& a_2, const Point& b_2) {
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
  if (ScalarMultiplication(-vector_a_1_b_2, -vector_b_1_b_2) <= 0) {
    return true;
  }
  return false;
}

bool Check(const Point& a_1, const Point& b_1, const Point& a_2, const Point& b_2) {
  if ((a_1 == a_2) || (a_1 == b_2) || (b_1 == a_2) || (b_1 == b_2)) {
    return true;
  }
  Vector vector_a_1_b_1(a_1, b_1);
  Vector vector_a_2_b_2(a_2, b_2);
  Vector vector_a_1_a_2(a_1, a_2);
  Vector vector_a_1_b_2(a_1, b_2);
  Vector vector_a_2_b_1(a_2, b_1);
  int64_t mult_2_3 = VectorMultiplication(vector_a_2_b_2, -vector_a_1_a_2);
  int64_t mult_2_5 = VectorMultiplication(vector_a_2_b_2, vector_a_2_b_1);
  int64_t mult_1_3 = VectorMultiplication(vector_a_1_b_1, vector_a_1_a_2);
  int64_t mult_1_4 = VectorMultiplication(vector_a_1_b_1, vector_a_1_b_2);
  if (std::abs(mult_2_3) + std::abs(mult_2_5) + std::abs(mult_1_3) + std::abs(mult_1_4) == 0) {
    return BorderCheck(a_1, b_1, a_2, b_2);
  }
  if (mult_1_3 != 0) {
    mult_1_3 /= std::abs(mult_1_3);
  }
  if (mult_2_3 != 0) {
    mult_2_3 /= std::abs(mult_2_3);
  }
  if (mult_2_5 != 0) {
    mult_2_5 /= std::abs(mult_2_5);
  }
  if (mult_1_4 != 0) {
    mult_1_4 /= std::abs(mult_1_4);
  }
  return ((mult_2_3 * mult_2_5 <= 0) && (mult_1_3 * mult_1_4 <= 0));
}

bool InThePoligon(const Point& point, const Polygon& poligon) {
  if (OnTheBorder(point, poligon)) {
    return true;
  }
  if (poligon.amount < 3) {
    return false;
  }
  for (int i = 0; i < poligon.amount - 1; ++i) {
    Vector v_1(poligon.sides[i].a, poligon.sides[i].b);
    Vector v_2(poligon.sides[i].a, point);
    Vector v_3(poligon.sides[i + 1].a, poligon.sides[i + 1].b);
    Vector v_4(poligon.sides[i + 1].a, point);
    if ((VectorMultiplication(v_1, v_2) == 0) || (VectorMultiplication(v_3, v_4) == 0)) {
      return false;
    }
    int64_t a = VectorMultiplication(v_1, v_2) / std::abs(VectorMultiplication(v_1, v_2));
    int64_t b = VectorMultiplication(v_3, v_4) / std::abs(VectorMultiplication(v_3, v_4));
    if (a * b <= 0) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int amount_social;
  std::cin >> amount_social;
  std::vector<Point> social_vertex(amount_social);
  std::vector<Polygon> shells(amount_social);
  for (int i = 0; i < amount_social; ++i) {
    std::cin >> social_vertex[i];
  }
  int amount_scientific;
  std::cin >> amount_scientific;
  std::vector<PointInZone> scientific_vertex(amount_scientific);
  for (int i = 0; i < amount_scientific; ++i) {
    std::cin >> scientific_vertex[i];
  }
  int iteration = 0;
  do {
    FirstPoint(amount_social, social_vertex);
    Point start = social_vertex[0];
    for (int i = 1; i < amount_social; ++i) {
      social_vertex[i] = social_vertex[i] - start;
    }
    std::sort(social_vertex.begin() + 1, social_vertex.begin() + amount_social);
    for (int i = 1; i < amount_social; ++i) {
      social_vertex[i] = social_vertex[i] + start;
    }
    shells[iteration] = ShellSearch(amount_social, social_vertex);
    for (int i = 0; i < amount_scientific; ++i) {
      if (InThePoligon(scientific_vertex[i].point, shells[iteration])) {
        scientific_vertex[i].zone = iteration;
      }
    }
    ++iteration;
    if (amount_social < 3) {
      break;
    }
  } while ((shells[iteration - 1].amount > 3));
  for (int i = 0; i < amount_scientific; ++i) {
    std::cout << scientific_vertex[i] << '\n';
  }
  return 0;
}
