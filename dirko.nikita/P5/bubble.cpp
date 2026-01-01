#include "shapes.hpp"

dirko::Bubble::Bubble(double r, p_t dot) noexcept:
  r_(r),
  dot_(dot)
{}
double dirko::Bubble::getArea() const noexcept
{
  return PI * r_ * r_;
}
dirko::rec_t dirko::Bubble::getFrameRect() const noexcept
{
  p_t tmp = {dot_.x + r_ / 2, dot_.y};
  return {r_, r_, tmp};
}
void dirko::Bubble::move(p_t point) noexcept
{
  dot_ = point;
}
void dirko::Bubble::move(double dx, double dy) noexcept
{
  dot_.x += dx;
  dot_.y += dy;
}
void dirko::Bubble::scale_(double coef) noexcept
{
  r_ *= coef;
}
