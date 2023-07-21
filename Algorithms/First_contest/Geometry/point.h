#include "ishape.h"
#ifndef POINT_H
#define POINT_H
namespace geometry {
  class Point : public IShape {
  private:
    friend Point& operator+=(Point&, const Vector&);
    friend Point& operator-=(Point&, const Point&);
    friend Vector operator-(const Point&, const Point&);
    int64_t x_;
    int64_t y_;
  public:
    Point();
    Point(const int64_t&, const int64_t&);
    explicit Point(const Vector&);
    ~Point() override;
    int64_t GetX() const;
    int64_t GetY() const;
    int64_t LenSqr() const;
    Point& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Point* Clone() const override;
    std::string ToString() const override;
  };
  bool operator==(const Point&, const Point&);
}
#endif
