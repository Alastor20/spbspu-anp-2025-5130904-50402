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
    private:
      r_t data;
    public:
      explicit Rectangle(const r_t& dd);
      double getArea() const override;
      lavrentev::r_t getFrameRect() const override;
      void move(const lavrentev::p_t& c) override;
      void move(double d_x, double d_y) override;
  };
}

int main()
{

}

