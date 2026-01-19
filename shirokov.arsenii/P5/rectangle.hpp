#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "pods.hpp"
#include "shape.hpp"

namespace shirokov
{
  struct Rectangle final: Shape
  {
    Rectangle(point_t center, double width, double height) noexcept;
    Rectangle(point_t bottomLeft, point_t topRight) noexcept;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(point_t target) noexcept override;
    void move(double x, double y) noexcept override;

  private:
    point_t center_, bottomLeft_, topRight_;
    void scale(double coefficient) noexcept override;
  };
}

#endif
