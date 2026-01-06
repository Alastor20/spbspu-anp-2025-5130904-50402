#include <cstddef>
#include <ctime>
#include <stdexcept>
#include <utility>
#include "shape_vec.hpp"

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
  shps_(other.size_ > 0 ? new Shape *[other.size_]() : nullptr),
  size_(0)
{
  try {
    for (size_t i = 0; i < other.size_; ++i) {
      shps_[i] = other.shps_[i]->clone();
      ++size_;
    }
  } catch (...) {
    for (size_t i = 0; i < size_; ++i) {
      delete shps_[i];
    }
    delete[] shps_;
    throw;
  }
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
  Shape_vec tmp(other);
  std::swap(tmp.shps_, this->shps_);
  std::swap(tmp.size_, this->size_);
  return *this;
}

dirko::rec_t dirko::Shape_vec::getFrameRect() const noexcept
{
  return getTotalFrame(shps_, size_);
}

void dirko::Shape_vec::scale_(double coef) noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    shps_[i]->doScale(coef);
  }
}

void dirko::Shape_vec::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    shps_[i]->move(dx, dy);
  }
}

void dirko::Shape_vec::move(p_t point) noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    shps_[i]->move(point);
  }
}

double dirko::Shape_vec::getArea() const noexcept
{
  double area = 0;
  for (size_t i = 0; i < size_; ++i) {
    area += shps_[i]->getArea();
  }
  return area;
}

dirko::Shape *dirko::Shape_vec::clone() const
{
  throw std::runtime_error("DO NOT USE DIRECTLY ON SHAPE_VEC");
}
