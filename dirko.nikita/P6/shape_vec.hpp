#ifndef SHAPE_VEC
#define SHAPE_VEC
#include "../common/shapesUtil.hpp"
namespace dirko
{
  struct Shape_vec final: Shape
  {
    Shape_vec();
    Shape_vec(const Shape_vec &);
    Shape_vec(Shape_vec &&);
    Shape_vec &operator=(const Shape_vec &);
    Shape_vec &operator=(Shape_vec &&);
    ~Shape_vec() noexcept override;
    double getArea() const noexcept override;
    rec_t getFrameRect() const noexcept override;
    void move(p_t point) noexcept override;
    void move(double dx, double dy) noexcept override;
    Shape *clone() const override;
    void doScale(double coef) noexcept;
    void doScaleSafe(double coef);

  private:
    Shape **shps_;
    size_t size_;
    void scale_(double coef) noexcept override;
  };
}
#endif
