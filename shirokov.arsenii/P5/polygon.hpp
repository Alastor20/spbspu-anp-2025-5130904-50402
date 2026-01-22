#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "pods.hpp"
#include "shape.hpp"
#include <cstddef>

namespace shirokov
{
  struct Polygon final: Shape
  {
    Polygon(const point_t *vertices, size_t s);
    ~Polygon() noexcept;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(point_t target) noexcept override;
    void move(double dx, double dy) noexcept override;
    void scale(double coefficient) noexcept override;

  private:
    size_t s_;
    point_t *vertices_;
    double signedDoubleArea;
    point_t center_;
    point_t setCenter(const point_t *vertices, size_t s);
    double setSignedArea(const point_t *vertices, size_t s);
  };
}

#endif
