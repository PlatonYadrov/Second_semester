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
  Line::Line() : a_(0), b_(0), c_(0), p_one_(Point()), p_two_(Point()) {
  }

  Line::Line(const int64_t& a_input, const int64_t& b_input, const int64_t& c_input) : a_(a_input), b_(b_input), c_(c_input), p_one_(Point()), p_two_(Point()) {
  }

  bool OnLine(const Point& a, const Point& b, const Point& c) {
    if (a == c or b == c) {
      return true;
    }
    Vector vector_a_b(a, b);
    Vector vector_a_c(a, c);
    Vector vector_b_c(b, c);
    return VectorMultiplication(vector_a_b, vector_a_c) == 0;
  }

  Line::Line(const Point& point_1, const Point& point_2) {
    a_ = point_1.GetY() - point_2.GetY();
    b_ = point_2.GetX() - point_1.GetX();
    c_ = point_1.GetX() * point_2.GetY() - point_2.GetX() * point_1.GetY();
    p_one_ = point_1;
    p_two_ = point_2;
  }

  Line::~Line() = default;

  int64_t Line::GetA() const {
    return a_;
  }

  int64_t Line::GetB() const {
    return b_;
  }

  int64_t Line::GetC() const {
    return c_;
  }

  Line& Line::Move(const Vector& vector) {
    p_one_ += vector;
    p_two_ += vector;
    a_ = p_one_.GetY() - p_two_.GetY();
    b_ = p_two_.GetX() - p_one_.GetX();
    c_ = p_one_.GetX() * p_two_.GetY() - p_two_.GetX() * p_one_.GetY();
    return *this;
  }

  bool Line::ContainsPoint(const Point& point) const {
    return (a_ * point.GetX() + b_ * point.GetY() + c_ == 0);
  }

  bool Line::CrossesSegment(const Segment& segment) const {
    return ((a_ * segment.GetOne().GetX() + b_ * segment.GetOne().GetY() + c_) * (a_ * segment.GetTwo().GetX() + b_ * segment.GetTwo().GetY() + c_) <= 0);
  }

  Line* Line::Clone() const {
    auto* line = new Line;
    *line = *this;
    return line;
  }

  std::string Line::ToString() const {
    std::string a_str = std::to_string(a_);
    std::string b_str = std::to_string(b_);
    std::string c_str = std::to_string(c_);
    std::string string = "Line(" + a_str + ", " + b_str + ", " + c_str + ")";
    return string;
  }
}
