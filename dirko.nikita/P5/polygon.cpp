#include <stdexcept>
#include "shapes.hpp"

double dirko::getPolArea(p_t *pts, size_t size)
{
  double area = 0;
  for (size_t i = 0; i < size; ++i) {
    size_t j = (i + 1) % size;
    area += pts[i].x * pts[j].y;
    area -= pts[j].x * pts[i].y;
  }
  area = std::abs(area) / 2;
  return area;
}
dirko::p_t dirko::getPolMid(p_t *pts, size_t size)
{
  double area = getPolArea(pts, size);
  p_t mid{};
  double factor = 0.0;
  for (size_t i = 0; i < size; ++i) {
    size_t j = (i + 1) % size;
    factor = (pts[i].x * pts[j].y - pts[j].x * pts[i].y);
    mid.x += (pts[i].x + pts[j].x) * factor;
    mid.y += (pts[i].y + pts[j].y) * factor;
  }
  mid.x /= (6.0 * area);
  mid.y /= (6.0 * area);
  return mid;
}
dirko::Polygon::Polygon(size_t size, p_t *pts):
  size_(size),
  pts_(pts),
  mid_(getPolMid(pts, size))
{
  if (size < 3) {
    throw std::logic_error("Cant create polygon");
  }
}
double dirko::Polygon::getArea() const noexcept
{
  return getPolArea(pts_, size_);
}
dirko::rec_t dirko::Polygon::getFrameRect() const noexcept
{
  double maxx = pts_[0].x, minx = pts_[0].x;
  double maxy = pts_[0].y, miny = pts_[0].y;
  for (size_t i = 1; i < size_; ++i) {
    maxx = std::max(maxx, pts_[i].x);
    minx = std::min(minx, pts_[i].x);
    maxy = std::max(maxy, pts_[i].y);
    miny = std::min(miny, pts_[i].y);
  }
  double w = maxx - minx;
  double h = maxy - miny;
  return {w, h, {maxx - w / 2, maxy - h / 2}};
}
void dirko::Polygon::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    pts_[i].x += dx;
    pts_[i].y += dy;
  }
  mid_.x += dx;
  mid_.y += dy;
}
void dirko::Polygon::move(p_t point) noexcept
{
  double dx = point.x - mid_.x;
  double dy = point.y - mid_.y;
  move(dx, dy);
}
void dirko::Polygon::scale_(double coef) noexcept
{
  double dx = 0, dy = 0;
  for (size_t i = 0; i < size_; ++i) {
    dx = pts_[i].x - mid_.x;
    dy = pts_[i].y - mid_.y;
    pts_[i].x += dx * (coef - 1);
    pts_[i].y += dy * (coef - 1);
  }
}
