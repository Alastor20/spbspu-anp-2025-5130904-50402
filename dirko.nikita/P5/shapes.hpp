#ifndef SHAPES
#define SHAPES
#include <cmath>
#include <shapesUtil.hpp>
namespace dirko
{
  const double PI = std::acos(-1.0);
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
    void scale_(double coef) noexcept override;
  };
  struct Polygon final: Shape
  {
    Polygon(size_t size, p_t *pts);
    ~Polygon() noexcept override;
    Polygon(const Polygon &);
    Polygon(Polygon &&) noexcept;
    Polygon &operator=(const Polygon &);
    Polygon &operator=(Polygon &&) noexcept;
    double getArea() const noexcept override;
    rec_t getFrameRect() const noexcept override;
    void move(double dx, double dy) noexcept override;
    void move(p_t point) noexcept override;

  private:
    size_t size_;
    p_t *pts_;
    p_t mid_;
    void scale_(double coef) noexcept override;
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
    void scale_(double coef) noexcept override;
  };
}
#endif
