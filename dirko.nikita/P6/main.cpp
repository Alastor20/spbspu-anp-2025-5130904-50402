#include <cstddef>
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
    ~Shape_vec() noexcept;
    double getArea() const noexcept;
    rec_t getFrameRect() const noexcept;
    void move(p_t point) noexcept;
    void move(double dx, double dy) noexcept;
    void doScale(double coef) noexcept;
    void doScaleSafe(double coef);

  private:
    Shape *shps_;
    size_t size_;
    size_t cap_;
    void scale(double coef) noexcept;
  };
}
int main()
{}
