#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
namespace dirko
{
  const double PI = std::acos(-1.0);
  struct p_t
  {
    double x, y;
  };
  struct rec_t
  {
    double w, h;
    p_t pos;
  };
  struct Shape
  {
    virtual ~Shape() noexcept = default;
    virtual double getArea() const noexcept = 0;
    virtual rec_t getFrameRect() const noexcept = 0;
    virtual void move(p_t point) noexcept = 0;
    virtual void move(double dx, double dy) noexcept = 0;
    void doScale(double coef) noexcept;
    void doScaleSafe(double coef);

  private:
    virtual void scale(double coef) noexcept = 0;
  };
  struct Rectangle final: Shape
  {
    Rectangle(double w, double h, p_t mid) noexcept;
    double getArea() const noexcept override;
    rec_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(p_t point) noexcept override;

  private:
    double w_, h_;
    p_t mid_;
    void scale(double coef) noexcept override;
  };
  struct Polygon final: Shape
  {
    Polygon(size_t size, p_t *pts);
    double getArea() const noexcept override;
    rec_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(p_t point) noexcept override;

  private:
    size_t size_;
    p_t *pts_;
    p_t mid_;
    void scale(double coef) noexcept override;
  };
  struct Bubble final: Shape
  {
    Bubble(double r, p_t dot) noexcept;
    double getArea() const noexcept override;
    rec_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(p_t point) noexcept override;

  private:
    double r_;
    p_t dot_;
    void scale(double coef) noexcept override;
  };
  void scaleFromPoint(Shape **shps, size_t size, p_t point, double coef);
  rec_t getTotalFrame(const Shape *const *shps, size_t size);
  std::ostream &output(std::ostream &os, const Shape *const *shps, size_t size);
  double getPolArea(p_t *pts, size_t size);
  p_t getPolMid(p_t *pts, size_t size);
}
int main()
{
  constexpr size_t pol_n = 5;
  constexpr size_t n = 3;
  dirko::Rectangle rec{5, 7, {3, 3}};
  dirko::Bubble bub{5, {2, 0}};
  dirko::p_t pts[pol_n] = {{2, 2}, {2, 7}, {2.5, 8}, {3, 7}, {3, 2}};
  dirko::Polygon pol(pol_n, pts);
  dirko::Shape *shps[n] = {std::addressof(rec), std::addressof(bub), std::addressof(pol)};
  std::cout << "Before scale:\n\n";
  dirko::output(std::cout, shps, n);
  dirko::p_t point = {};
  double coef = 0;
  if (!(std::cin >> point.x >> point.y >> coef)) {
    std::cerr << "Cant read\n";
    return 1;
  }
  if (coef <= 0) {
    std::cerr << "Non positive coef\n";
    return 1;
  }
  try {
    dirko::scaleFromPoint(shps, n, point, coef);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  std::cout << "\n\nAfter scale:\n\n";
  dirko::output(std::cout, shps, n);
}
void dirko::Shape::doScale(double coef) noexcept
{
  scale(coef);
}
void dirko::Shape::doScaleSafe(double coef)
{
  if (coef <= 0) {
    throw std::invalid_argument("Non positive coef");
  }
  scale(coef);
}
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
void dirko::Rectangle::scale(double coef) noexcept
{
  w_ *= coef;
  h_ *= coef;
}
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
void dirko::Polygon::scale(double coef) noexcept
{
  double dx = 0, dy = 0;
  for (size_t i = 0; i < size_; ++i) {
    dx = pts_[i].x - mid_.x;
    dy = pts_[i].y - mid_.y;
    pts_[i].x += dx * (coef - 1);
    pts_[i].y += dy * (coef - 1);
  }
}
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
void dirko::Bubble::scale(double coef) noexcept
{
  r_ *= coef;
}
void dirko::scaleFromPoint(Shape **shps, size_t size, p_t point, double coef)
{
  for (size_t i = 0; i < size; ++i) {
    rec_t fr = shps[i]->getFrameRect();
    double dx = (fr.pos.x - point.x) * (coef - 1);
    double dy = (fr.pos.y - point.y) * (coef - 1);
    shps[i]->move(dx, dy);
    shps[i]->doScaleSafe(coef);
  }
}
dirko::rec_t dirko::getTotalFrame(const Shape *const *shps, size_t size)
{
  if (size == 0) {
    return {0.0, 0.0, {0.0, 0.0}};
  }
  rec_t frame = shps[0]->getFrameRect();
  double left = frame.pos.x - frame.w / 2.0;
  double right = frame.pos.x + frame.w / 2.0;
  double bottom = frame.pos.y - frame.h / 2.0;
  double top = frame.pos.y + frame.h / 2.0;
  for (size_t i = 1; i < size; ++i) {
    frame = shps[i]->getFrameRect();
    double l = frame.pos.x - frame.w / 2.0;
    double r = frame.pos.x + frame.w / 2.0;
    double b = frame.pos.y - frame.h / 2.0;
    double t = frame.pos.y + frame.h / 2.0;
    left = std::min(l, left);
    right = std::max(r, right);
    bottom = std::min(b, bottom);
    top = std::max(t, top);
  }
  rec_t total;
  total.w = right - left;
  total.h = top - bottom;
  total.pos.x = (left + right) / 2.0;
  total.pos.y = (bottom + top) / 2.0;
  return total;
}
std::ostream &dirko::output(std::ostream &os, const Shape *const *shps, size_t size)
{
  double totalArea = 0.0;
  for (size_t i = 0; i < size; ++i) {
    double area = shps[i]->getArea();
    totalArea += area;
    os << "shape " << i + 1 << " area: " << area << "\n";
    rec_t frame = shps[i]->getFrameRect();
    os << "shape " << i + 1 << " frame x: " << frame.pos.x << "\n";
    os << "shape " << i + 1 << " frame y: " << frame.pos.y << "\n";
    os << "shape " << i + 1 << " frame width: " << frame.w << "\n";
    os << "shape " << i + 1 << " frame height: " << frame.h << "\n";
  }
  rec_t totalFrame = getTotalFrame(shps, size);
  os << "Total area: " << totalArea << "\n";
  os << "Total frame x: " << totalFrame.pos.x << "\n";
  os << "Total frame y: " << totalFrame.pos.y << "\n";
  os << "Total frame width: " << totalFrame.w << "\n";
  os << "Total frame height: " << totalFrame.h << "\n";
  return os;
}
