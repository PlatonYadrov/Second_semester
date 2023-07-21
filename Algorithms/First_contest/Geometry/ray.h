#include "ishape.h"
#ifndef RAY_H
#define RAY_H
namespace geometry {
  class Ray : public IShape { 
  private:
    Point p_one_;
    Point p_two_;
  public:
    Ray();
    Ray(const Point&, const Point&);
    ~Ray() override;
    Point GetOne() const;
    Point GetTwo() const;
    Ray& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Ray* Clone() const override;
    std::string ToString() const override;
  };
}
#endif
