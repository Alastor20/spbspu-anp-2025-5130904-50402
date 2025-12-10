#include <iostream>
#include <stdexcept>

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
      void scale(double coef) override;
  };
}

int main()
{

}

lavrentev::Rectangle::Rectangle(const r_t& dd) : data(dd)
{
    if (dd.width <= 0 || dd.height <= 0)
    {
        throw std::invalid_argument("Invalid weight or height");
    }
}

double lavrentev::Rectangle::getArea() const
{
    return data.width * data.height;
}

lavrentev::r_t lavrentev::Rectangle::getFrameRect() const
{
    return data;
}

void lavrentev::Rectangle::move(const lavrentev::p_t& c)
{
    data.pos = c;
}

void lavrentev::Rectangle::move(double x, double y)
{
    data.pos.x += x;
    data.pos.y += y;
}

void lavrentev::Rectangle::scale(double coef)
{
    if (coef <= 0)
    {
        throw std::invalid_argument("Coef must be positive");
    }
    data.width *= coef;
    data.height *= coef;
}
