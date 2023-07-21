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
  Ray::Ray() : p_one_(Point()), p_two_(Point()) {
  }

  Ray::Ray(const Point& p_1, const Point& p_2) : p_one_(p_1), p_two_(p_2) {
  }

  Ray::~Ray() = default;

  Point Ray::GetOne() const {
    return p_one_;
  }

  Point Ray::GetTwo() const {
    return p_two_;
  }

  Ray& Ray::Move(const Vector& vector) {
    p_one_ += vector;
    p_two_ += vector;
    return *this;
  }

  bool OnRay(const Point& a, const Point& b, const Point& c) {
    if (!OnLine(a, b, c)) {
      return false;
    }
    Vector vector_a_b(a, b);
    Vector vector_a_c(a, c);
    Vector vector_b_c(b, c);
    return ScalarMultiplication(vector_a_b, vector_a_c) >= 0;
  }

  bool Ray::ContainsPoint(const Point& p) const {
    return OnRay(p_one_, p_two_, p);
  }

  bool Ray::CrossesSegment(const Segment& s) const {
    if (OnRay(p_one_, p_two_, s.GetOne()) || OnRay(p_one_, p_two_, s.GetTwo())) {
      return true;
    }
    Vector vector_a_o(s.GetOne(), p_one_);
    Vector vector_a_b(s.GetOne(), s.GetTwo());
    Vector v(p_one_, p_two_);
    return (VectorMultiplication(vector_a_o, vector_a_b) * VectorMultiplication(v, vector_a_b) < 0);
  }

  Ray* Ray::Clone() const {
    auto* ray = new Ray;
    *ray = *this;
    return ray;
  }

  std::string Ray::ToString() const {
    Vector v(p_one_, p_two_);
    std::string string = "Ray(" + p_one_.ToString() + ", " + v.ToString() + ")";
    return string;
  }
}
