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
  Circle::Circle() : radius_(0), center_(Point()) {
  }

  Circle::Circle(const Point& c, const int64_t& r) : radius_(r), center_(c) {
  }

  Circle::~Circle() = default;

  Circle& Circle::Move(const Vector& vector) {
    center_ += vector;
    return *this;
  }

  bool Circle::ContainsPoint(const Point& point) const {
    Vector vector_1 = Vector(center_, point);
    return (vector_1.LenSqr() <= radius_ * radius_);
  }

  bool Circle::CrossesSegment(const Segment& segment) const {
    Point a = segment.GetOne();
    Point b = segment.GetTwo();
    Point c = center_;
    int radius_effective = radius_ * radius_;
    Vector vector_a_b(a, b);
    Vector vector_a_c(a, c);
    Vector vector_b_c(b, c);
    int64_t coefficient_x = a.GetY() - b.GetY();
    int64_t coefficient_y = b.GetX() - a.GetX();
    int64_t free_coefficient = a.GetX() * b.GetY() - b.GetX() * a.GetY();
    int64_t numerator_sqr = std::pow(coefficient_x * c.GetX() + coefficient_y * c.GetY() + free_coefficient, 2);
    int64_t denominator_sqr = std::pow(coefficient_x, 2) + std::pow(coefficient_y, 2);
    int64_t distance_a_c_sqr = std::pow(a.GetX() - c.GetX(), 2) + std::pow(a.GetY() - c.GetY(), 2);
    int64_t distance_b_c_sqr = std::pow(b.GetX() - c.GetX(), 2) + std::pow(b.GetY() - c.GetY(), 2);
    if (ScalarMultiplication(vector_a_b, vector_a_c) > 0) {
      if (ScalarMultiplication(vector_a_b, vector_b_c) < 0) {
        // distance_to_line_segmeit = DistanceToLine(a, b, c);
        if (numerator_sqr == radius_effective * denominator_sqr) {
          return true;
        }
        if (numerator_sqr < radius_effective * denominator_sqr) {
          Vector vector_1 = Vector(c, a);
          Vector vector_2 = Vector(c, b);
          return ((vector_1.LenSqr() - radius_ * radius_ >= 0) || (vector_2.LenSqr() - radius_ * radius_ >= 0));
        }
        return false;
      }
      // distance_to_line_segmeit = distance_b_c;
      if (distance_b_c_sqr == radius_effective) {
        return true;
      }
      if (distance_b_c_sqr < radius_effective) {
        Vector vector_1 = Vector(c, a);
        Vector vector_2 = Vector(c, b);
        return ((vector_1.LenSqr() - radius_ * radius_ >= 0) || (vector_2.LenSqr() - radius_ * radius_ >= 0));
      }
      return false;
    }
    // distance_to_line_segmeit = distance_a_c;
    if (distance_a_c_sqr == radius_effective) {
      return true;
    }
    if (distance_a_c_sqr < radius_effective) {
      Vector vector_1 = Vector(c, a);
      Vector vector_2 = Vector(c, b);
      return ((vector_1.LenSqr() - radius_ * radius_ >= 0) || (vector_2.LenSqr() - radius_ * radius_ >= 0));
    }
    return false;
  }

  Circle* Circle::Clone() const {
    auto* circle = new Circle;
    *circle = *this;
    return circle;
  }

  std::string Circle::ToString() const {
    std::string r_str = std::to_string(radius_);
    std::string string = "Circle(" + center_.ToString() + ", " + r_str + ")";
    return string;
  }
}
