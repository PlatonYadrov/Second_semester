#include "ishape.h"
#ifndef POLYGON_H
#define POLYGON_H
namespace geometry {
  class Polygon : public IShape { 
  private:
    friend bool OnePointOnTheBorder(const Point&, const Point&, const Point&);
    friend bool OnTheBorderPoligon(const Point&, const Polygon&);
    friend int64_t PointValue(const Line&, const Point&);
    friend bool IntersectioLlineWithSegment(const Line&, const Segment&);
    friend bool Inside(const Point&, const Polygon&);
    int64_t amount_;
    std::vector<Point> vertex_;
    std::vector<Segment> sides_;
  public:
    Polygon();
    explicit Polygon(const std::vector<Point>&);
    ~Polygon() override;
    bool PointInPolygon(Point) const;
    bool PolygonIntersectsSegment(Segment) const;
    Polygon& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Polygon* Clone() const override;
    std::string ToString() const override;
  };
}
#endif
