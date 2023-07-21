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
Vector::Vector() : x_(0), y_(0) {
  }

  Vector::Vector(const Point& point) : x_(point.GetX()), y_(point.GetY()) {
  }

  Vector::Vector(const int64_t& x_input, const int64_t& y_input) : x_(x_input), y_(y_input) {
  }

  Vector::Vector(const Point& point_1, const Point& point_2) : x_(point_2.GetX() - point_1.GetX()), y_(point_2.GetY() - point_1.GetY()) {
  }

  int64_t Vector::GetX() const {
    return x_;
  }

  int64_t Vector::GetY() const {
    return y_;
  }

  int64_t Vector::LenSqr() const {
    return x_ * x_ + y_ * y_;
  }

  Vector operator+(const Vector& vector_1, const Vector& vector_2) {
    return Vector(vector_1.x_ + vector_2.x_, vector_1.y_ + vector_2.y_);
  }

  Vector operator+(const Vector& vector_1) {
    return vector_1;
  }

  Vector& operator+=(Vector& vector_1, const Vector& vector_2) {
    vector_1.x_ += vector_2.x_;
    vector_1.y_ += vector_2.y_;
    return vector_1;
  }

  Point& operator+=(Point& point, const Vector& vector) {
    point.x_ += vector.GetX();
    point.y_ += vector.GetY();
    return point;
  }

  Vector operator-(const Vector& vector_1, const Vector& vector_2) {
    return Vector(vector_1.x_ - vector_2.x_, vector_1.y_ - vector_2.y_);
  }

  Vector operator-(const Point& point_1, const Point& point_2) {
    return Vector(point_1) - Vector(point_2);
  }

  Vector operator-(const Vector& vector_1) {
    return Vector(-vector_1.x_, -vector_1.y_);
  }

  Vector& operator-=(Vector& vector_1, const Vector& vector_2) {
    vector_1.x_ -= vector_2.x_;
    vector_1.y_ -= vector_2.y_;
    return vector_1;
  }

  Point& operator-=(Point& point_1, const Point& point_2) {
    point_1.x_ -= point_2.x_;
    point_1.y_ -= point_2.y_;
    return point_1;
  }

  Vector operator*(const int64_t& number, const Vector& vector) {
    return Vector(number * vector.x_, number * vector.y_);
  }

  Vector operator*(const Vector& vector, const int64_t& number) {
    return number * vector;
  }

  Vector& operator*=(Vector& vector, const int64_t& number) {
    vector.x_ *= number;
    vector.y_ *= number;
    return vector;
  }

  Vector operator/(const Vector& vector, const int64_t& number) {
    return Vector(vector.x_ / number, vector.y_ / number);
  }

  Vector& operator/=(Vector& vector, const int64_t& number) {
    vector.x_ /= number;
    vector.y_ /= number;
    return vector;
  }

  bool operator==(const Vector& vector_1, const Vector& vector_2) {
    return (vector_1.x_ * vector_2.y_ == vector_1.y_ * vector_2.x_);
  }

  std::string Vector::ToString() const {
    std::string x_str = std::to_string(x_);
    std::string y_str = std::to_string(y_);
    std::string string = "Vector(" + x_str + ", " + y_str + ")";
    return string;
  }
  
  int64_t ScalarMultiplication(Vector vector_1, Vector vector_2) {
    return vector_1.GetX() * vector_2.GetX() + vector_1.GetY() * vector_2.GetY();
  }

  int64_t VectorMultiplication(Vector vector_1, Vector vector_2) {
    return vector_1.GetX() * vector_2.GetY() - vector_1.GetY() * vector_2.GetX();
  }

  IShape::~IShape() = default;
}
