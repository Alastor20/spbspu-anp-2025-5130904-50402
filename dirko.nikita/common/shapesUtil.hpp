#ifndef SHAPES_UTIL
#define SHAPES_UTIL
#include <iosfwd>

namespace dirko
{
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
    virtual void scale_(double coef) noexcept = 0;
  };
  void scaleFromPoint(Shape **shps, size_t size, p_t point, double coef);
  rec_t getTotalFrame(const Shape *const *shps, size_t size);
  std::ostream &output(std::ostream &os, const Shape *const *shps, size_t size);
  double getPolArea(p_t *pts, size_t size);
  p_t getPolMid(p_t *pts, size_t size);
}
#endif
