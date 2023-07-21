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
  Segment::Segment() : p_one_(Point()), p_two_(Point()) {
  }

  Segment::Segment(const Point& point_1, const Point& point_2) : p_one_(point_1), p_two_(point_2) {
  }

  Segment::~Segment() = default;

  Segment& Segment::Move(const Vector& vector) {
    p_one_.Move(vector);
    p_two_.Move(vector);
    return *this;
  }

  Point Segment::GetOne() const {
    return p_one_;
  }

  Point Segment::GetTwo() const {
    return p_two_;
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

  bool Segment::ContainsPoint(const Point& point) const {
    if ((p_one_ == point) || (p_two_ == point)) {
      return true;
    }
    Vector vector_a_b(p_one_, p_two_);
    Vector vector_a_c(p_one_, point);
    Vector vector_b_c(p_two_, point);
    if (VectorMultiplication(vector_a_b, vector_a_c) == 0) {
      if (ScalarMultiplication(vector_a_b, vector_a_c) > 0) {
        if (ScalarMultiplication(vector_a_b, vector_b_c) < 0) {
          return true;
        }
      }
    }
    return false;
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

  bool Segment::CrossesSegment(const Segment& segment) const {
    return Intersection(segment.p_one_, segment.p_two_, p_one_, p_two_);
  }

  Segment* Segment::Clone() const {
    auto* segment = new Segment;
    *segment = *this;
    return segment;
  }

  std::string Segment::ToString() const {
    std::string string = "Segment(" + p_one_.ToString() + ", " + p_two_.ToString() + ")";
    return string;
  }
}
