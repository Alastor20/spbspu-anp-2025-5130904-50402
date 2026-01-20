#include "polygon.hpp"
#include <algorithm>
#include <cstdlib>

shirokov::Polygon::Polygon(const point_t *vertices, size_t s):
  center_({0, 0}),
  vertices_(new point_t[s]),
  s_(s),
  signedDoubleArea(0)
{
  for (size_t i = 0; i < s; ++i)
  {
    vertices_[i] = vertices[i];
  }

  double cx = 0, cy = 0;
  for (size_t i = 0; i < s; ++i)
  {
    double xi = vertices_[i].x;
    double yi = vertices_[i].y;
    size_t j = (i + 1) % s_;
    double xj = vertices_[j].x;
    double yj = vertices_[j].y;
    double cross = xi * yj - xj * yi;
    signedDoubleArea += cross;
    cx += (xi + xj) * cross;
    cy += (yi + yj) * cross;
  }
  signedDoubleArea *= 0.5;
  cx /= 6 * signedDoubleArea;
  cy /= 6 * signedDoubleArea;

  center_ = {cx, cy};
}

double shirokov::Polygon::getArea() const noexcept
{
  return std::abs(signedDoubleArea);
}

shirokov::rectangle_t shirokov::Polygon::getFrameRect() const noexcept
{
  double maxx = vertices_[0].x, minx = vertices_[0].x, maxy = vertices_[0].y, miny = vertices_[0].y;
  for (size_t i = 0; i < s_; ++i)
  {
    maxx = std::max(maxx, vertices_[i].x);
    minx = std::min(minx, vertices_[i].x);
    maxy = std::max(maxy, vertices_[i].y);
    miny = std::min(miny, vertices_[i].y);
  }
  double width = maxx - minx;
  double height = maxy - miny;
  point_t pos = {(minx + maxx) / 2, (miny + maxy) / 2};
  return {width, height, pos};
}

void shirokov::Polygon::move(point_t target) noexcept
{
  point_t delta = {center_.x - target.x, center_.y - target.y};
  center_ = target;
  for (size_t i = 0; i < s_; ++i)
  {
    vertices_[i] = {vertices_[i].x - delta.x, vertices_[i].y - delta.y};
  }
}

void shirokov::Polygon::move(double dx, double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
  for (size_t i = 0; i < s_; ++i)
  {
    vertices_[i].x += dx;
    vertices_[i].y += dy;
  }
}

void shirokov::Polygon::scale(double coefficient) noexcept
{
  for (size_t i = 0; i < s_; ++i)
  {
    vertices_[i] = {center_.x + coefficient * (vertices_[i].x - center_.x),
                    center_.y + coefficient * (vertices_[i].y - center_.y)};
  }
}

shirokov::Polygon::~Polygon() noexcept
{
  delete[] vertices_;
}
