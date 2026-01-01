#include "shapes.hpp"

dirko::Rectangle::Rectangle(double w, double h, p_t mid) noexcept:
  w_(w),
  h_(h),
  mid_(mid)
{}
double dirko::Rectangle::getArea() const noexcept
{
  return w_ * h_;
}
dirko::rec_t dirko::Rectangle::getFrameRect() const noexcept
{
  return {w_, h_, mid_};
}
void dirko::Rectangle::move(p_t point) noexcept
{
  mid_ = point;
}
void dirko::Rectangle::move(double dx, double dy) noexcept
{
  mid_.x += dx;
  mid_.y += dy;
}
void dirko::Rectangle::scale_(double coef) noexcept
{
  w_ *= coef;
  h_ *= coef;
}
