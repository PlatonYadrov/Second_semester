#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "../ishape.h"
#include "../vector.h"
#include "../point.h"
#include "../line.h"
#include "../ray.h"
#include "../segment.h"
#include "../polygon.h"
#include "../circle.h"
namespace geometry {
  Polygon::Polygon() : amount_(0) {
  }

  Polygon::Polygon(const std::vector<Point>& points) {
    amount_ = points.size();
    vertex_.resize(amount_);
    sides_.resize(amount_);
    for (int64_t i = 0; i < amount_; ++i) {
      vertex_[i] = points[i];
    }
    for (int64_t i = 0; i < amount_; ++i) {
      if (i == amount_ - 1) {
        sides_[i] = Segment(points[i], points[0]);
      } else {
        sides_[i] = Segment(points[i], points[i + 1]);
      }
    }
  }

  Polygon::~Polygon() = default;

  Polygon& Polygon::Move(const Vector& v) {
    for (int64_t i = 0; i < amount_; ++i) {
      vertex_[i] += v;
      sides_[i].Move(v);
    }
    return *this;
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

  bool OnTheBorderPoligon(const Point& verifiable, const Polygon& my_poligon) {
    for (int64_t i = 0; i < my_poligon.amount_; ++i) {
      if (OnePointOnTheBorder(my_poligon.sides_[i].GetOne(), my_poligon.sides_[i].GetTwo(), verifiable)) {
        return true;
      }
    }
    return false;
  }

  int64_t PointValue(const Line& line, const Point& point) {
    return line.GetA() * point.GetX() + line.GetB() * point.GetY() + line.GetC();
  }

  bool IntersectioLlineWithSegment(const Line& secant, const Segment& segment) {
    return PointValue(secant, segment.GetOne()) * PointValue(secant, segment.GetTwo()) < 0;
  }

  bool Inside(const Point& verifiable, const Polygon& my_poligon) {
    if (OnTheBorderPoligon(verifiable, my_poligon)) {
      return true;
    }
    Point p_1(1e5, verifiable.GetY() + 1);
    Line secant(verifiable, p_1);
    Vector v_secant(verifiable, p_1);
    int64_t count = 0;
    for (int64_t i = 0; i < my_poligon.amount_; ++i) {
      Segment present = my_poligon.sides_[i];
      Vector v_a_o(present.GetOne(), verifiable);
      Vector v_a_b(present.GetOne(), present.GetTwo());
      if (IntersectioLlineWithSegment(secant, present)) {
        if (VectorMultiplication(v_a_o, v_a_b) * VectorMultiplication(v_secant, v_a_b) < 0) {
          ++count;
        }
      }
    }
    return count % 2;
  }

  bool Polygon::ContainsPoint(const Point& point) const {
    return Inside(point, *this);
  }

  bool Polygon::CrossesSegment(const Segment& s) const {
    for (int64_t i = 0; i < amount_; ++i) {
      if (Intersection(s.GetOne(), s.GetTwo(), sides_[i].GetOne(), sides_[i].GetTwo())) {
        return true;
      }
    }
    return false;
  }

  Polygon* Polygon::Clone() const {
    auto* polygon = new Polygon;
    *polygon = *this;
    return polygon;
  }

  std::string Polygon::ToString() const {
    std::string string = "Polygon(";
    for (int64_t i = 0; i < amount_; ++i) {
      if (i == amount_ - 1) {
        string += vertex_[amount_ - 1].ToString() + ")";
      } else {
        string += vertex_[i].ToString() + ", ";
      }
    }
    return string;
  }
}
