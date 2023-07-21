#include "ishape.h"
#ifndef SEGMENT_H
#define SEGMENT_H
namespace geometry {
  class Segment : public IShape {
  private:
    Point p_one_;
    Point p_two_;
  public:
    Segment();
    Segment(const Point&, const Point&);
    ~Segment() override;
    Point GetOne() const;
    Point GetTwo() const;
    Segment& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Segment* Clone() const override;
    std::string ToString() const override;
  };
}
#endif
