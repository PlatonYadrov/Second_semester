#include "ishape.h"
#ifndef VECTOR_H
#define VECTOR_H
namespace geometry {
  class Vector {
  private:
    friend Vector operator+(const Vector&, const Vector&);
    friend Vector operator+(const Vector&);
    friend Vector& operator+=(Vector&, const Vector&);
    friend Vector operator-(const Vector&, const Vector&);
    friend Vector operator-(const Vector&);
    // friend Vector operator-(const Point&, const Point&);
    friend Vector operator*(const int64_t&, const Vector&);
    friend Vector operator*(const Vector&, const int64_t&);
    friend Vector& operator*=(Vector&, const int64_t&);
    friend Vector operator/(const Vector&, const int64_t&);
    friend Vector& operator/=(Vector&, const int64_t&);
    friend bool operator==(const Vector&, const Vector&);
    int64_t x_;
    int64_t y_;
  public:
    friend Vector& operator-=(Vector&, const Vector&);
    Vector();
    explicit Vector(const Point&);
    Vector(const Point&, const Point&);
    Vector(const int64_t&, const int64_t&);
    int64_t GetX() const;
    int64_t GetY() const;
    std::string ToString() const;
    int64_t LenSqr() const;
  };

  int64_t ScalarMultiplication(Vector, Vector);
  int64_t VectorMultiplication(Vector, Vector);
  bool OnLine(const Point&, const Point&, const Point&);
  bool OnRay(const Point&, const Point&, const Point&);
  bool OnLineSegment(const Point&, const Point&, const Point&);
  bool OnTheBorder(const Point&, const Point&, const Point&, const Point&);
  bool Intersection(const Point&, const Point&, const Point&, const Point&);
  bool OnePointOnTheBorder(const Point&, const Point&, const Point&);
  bool OnTheBorderPoligon(const Point&, const Polygon&);
  int64_t PointValue(const Line&, const Point&);
  bool IntersectioLlineWithSegment(const Line&, const Segment&);
  bool Inside(const Point&, const Polygon&);
  bool IntersectionCircle(const Point&, const Point&, const Point&, const int&);
}
#endif
