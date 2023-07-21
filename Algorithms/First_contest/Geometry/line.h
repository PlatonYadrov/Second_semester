#include "ishape.h"
#ifndef LINE_H
#define LINE_H
namespace geometry {
  class Line;
  class Line : public IShape {
  private:
    int64_t a_;
    int64_t b_;
    int64_t c_;
    Point p_one_;
    Point p_two_;
  public:
    Line();
    Line(const int64_t&, const int64_t&, const int64_t&);
    Line(const Point&, const Point&);
    ~Line() override;
    int64_t GetA() const;
    int64_t GetB() const;
    int64_t GetC() const;
    Line& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Line* Clone() const override;
    std::string ToString() const override;
  };
}
#endif
