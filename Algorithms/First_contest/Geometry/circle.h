#include "vector.h"
#ifndef CIRCLE_H
#define CIRCLE_H
namespace geometry {
  class Circle : public IShape {
    public:
    int64_t radius;
    Point center;
    Circle();
    Circle(const Point&, const int64_t&);
    ~Circle() override;
    bool CircleIntersectsSegment(Segment) const;
    IShape& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    IShape* Clone() const override;
    std::string ToString() const override;
  };
}
#endif
