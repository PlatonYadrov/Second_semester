#include "ishape.h"
#ifndef CIRCLE_H
#define CIRCLE_H
namespace geometry {
  class Circle : public IShape {
    private:
    int64_t radius_;
    Point center_;
    public:
    Circle();
    Circle(const Point&, const int64_t&);
    ~Circle() override;
    bool CircleIntersectsSegment(Segment) const;
    Circle& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Circle* Clone() const override;
    std::string ToString() const override;
  };
}
#endif
