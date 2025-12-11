#include <iostream>
#include <stdexcept>
#include <cmath>

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

  struct ru_t
  {
    p_t pos;
    p_t outCenter;
    double rPos;
    double rOut;
  };

  struct pol_t
  {
    p_t pos;
    p_t* vertexes[];
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

  struct Rubber: Shape
  {
    private:
      ru_t data;
    public:
      explicit Rubber(const ru_t& dd);
      double getArea() const override;
      lavrentev::r_t getFrameRect() const override;
      void move(const lavrentev::p_t& c) override;
      void move(double d_x, double d_y) override;
      void scale(double coef) override;
  };

  struct Polygon: Shape
  {
    private:
      pol_t data;
    public:
      explicit Polygon(const pol_t& dd);
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

void lavrentev::Rectangle::move(double d_x, double d_y)
{
    data.pos.x += d_x;
    data.pos.y += d_y;
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

lavrentev::Rubber::Rubber(const ru_t& dd) : data(dd)
{
    if(dd.rOut <= 0 || dd.rPos <= 0)
    {
        throw std::invalid_argument("Invalid value of radius");
    }
}

double lavrentev::Rubber::getArea() const
{
    return M_PI * data.rOut * data.rOut - M_PI * data.rPos * data.rPos;
}

lavrentev::r_t lavrentev::Rubber::getFrameRect() const
{
    lavrentev::r_t ans;
    ans.pos = data.outCenter;
    ans.height = data.rOut * 2;
    ans.width = data.rOut * 2;
    return ans;
}

void lavrentev::Rubber::move(const lavrentev::p_t& c)
{
    data.pos = c;
}

void lavrentev::Rubber::move(double d_x, double d_y)
{
    data.pos.x += d_x;
    data.pos.y += d_y;
}

void lavrentev::Rubber::scale(double coef)
{
    if (coef <= 0)
    {
        throw std::invalid_argument("Coef must be positive");
    }
    data.rPos *= coef;
    data.rOut *= coef;
}
