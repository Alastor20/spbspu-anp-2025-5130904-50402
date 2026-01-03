#include <algorithm>
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
    ~Shape_vec() noexcept override;
    double getArea() const noexcept override;
    rec_t getFrameRect() const noexcept override;
    void move(p_t point) noexcept override;
    void move(double dx, double dy) noexcept override;
    void doScale(double coef) noexcept;
    void doScaleSafe(double coef);

  private:
    Shape **shps_;
    size_t size_;
    void scale_(double coef) noexcept override;
  };
}
int main()
{}

dirko::Shape_vec::Shape_vec():
  shps_(nullptr),
  size_(0)
{}

dirko::Shape_vec::~Shape_vec() noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    delete shps_[i];
  }
  delete[] shps_;
}

dirko::Shape_vec::Shape_vec(const Shape_vec &other):
  shps_(new Shape *[other.size_]),
  size_(other.size_)
{
  // TODO: Still хз
}

dirko::Shape_vec::Shape_vec(Shape_vec &&r):
  shps_(r.shps_),
  size_(r.size_)
{
  r.shps_ = nullptr;
}

dirko::Shape_vec &dirko::Shape_vec::operator=(Shape_vec &&r)
{
  shps_ = r.shps_;
  r.shps_ = nullptr;
  size_ = r.size_;
  return *this;
}

dirko::Shape_vec &dirko::Shape_vec::operator=(const Shape_vec &other)
{
  // TODO: (┬┬﹏┬┬)
  return *this;
}
