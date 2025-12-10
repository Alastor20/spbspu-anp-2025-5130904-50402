#include <iostream>

namespace lavrentev
{
  struct p_t
  {
    double x, y;
  };

  struct r_t
  {
    double width, height;
    p_t pos;
  };

  struct Shape
  {
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual r_t getFrameRect() const = 0;
    virtual void move(const p_t& c) = 0;
    virtual void move(double d_x, double d_y) = 0;
    virtual void scale(double coef) = 0;
  };

  struct Rectangle: Shape
  {
    
  };
}

int main()
{

}