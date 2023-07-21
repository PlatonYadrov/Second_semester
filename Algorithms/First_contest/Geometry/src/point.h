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
  Point::Point() : x_(0), y_(0) {
  }

  Point::Point(const int64_t& x_input, const int64_t& y_input) : x_(x_input), y_(y_input) {
  }

  Point::Point(const Vector& vector) : x_(vector.GetX()), y_(vector.GetY()) {
  }

  Point::~Point() = default;

  int64_t Point::GetX() const {
    return x_;
  }

  int64_t Point::GetY() const {
    return y_;
  }

  int64_t Point::LenSqr() const {
    return x_ * x_ + y_ * y_;
  }

  bool operator==(const Point& point_1, const Point& point_2) {
    return ((point_1.GetX() == point_2.GetX()) && (point_1.GetY() == point_2.GetY()));
  }

  Point& Point::Move(const Vector& vector) {
    x_ += vector.GetX();
    y_ += vector.GetY();
    return *this;
  }

  bool Point::ContainsPoint(const Point& point) const {
    return ((x_ == point.x_) && (y_ == point.y_));
  }

  bool Point::CrossesSegment(const Segment& segment) const {
    return OnLineSegment(segment.GetOne(), segment.GetTwo(), *this);
  }

  Point* Point::Clone() const {
    auto* point = new Point;
    point->x_ = x_;
    point->y_ = y_;
    return point;
  }

  std::string Point::ToString() const {
    std::string x_str = std::to_string(x_);
    std::string y_str = std::to_string(y_);
    std::string string = "Point(" + x_str + ", " + y_str + ")";
    return string;
  }
}
