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
    virtual double getArea() const;
    virtual p_t* getFrameRect() const;
    virtual void move(p_t c);
    virtual void move(double d_x, double d_y);
  };
}

int main()
{

}