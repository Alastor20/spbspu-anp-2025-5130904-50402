#include <iostream>

namespace bukreev
{
  struct point_t
  {
    double x, y;
  };
  struct rectangle_t
  {
    point_t pos;
    double width, height;
  };

  struct Shape
  {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t newPos) = 0;
    virtual void move(double dX, double dY) = 0;
    virtual void scale(double k) = 0;
  };

  struct Rectangle : Shape
  {
    Rectangle(point_t center, double width, double height):
      mCenter(center),
      mWidth(width),
      mHeight(height)
    {}
    double getArea() const override
    {
      return mWidth * mHeight;
    }
    rectangle_t getFrameRect() const override
    {
      return rectangle_t{mCenter, mWidth, mHeight};
    }
    void move(point_t newPos) override
    {
      mCenter = newPos;
    }
    void move(double dX, double dY) override
    {
      mCenter.x += dX;
      mCenter.y += dY;
    }
    void scale(double k) override
    {
      mWidth *= k;
      mHeight *= k;
    }

  private:
    point_t mCenter;
    double mWidth, mHeight;
  };

  struct Xquare : Shape
  {
    Xquare(point_t center, double diagWidth):
      mCenter(center),
      mDiagWidth(diagWidth)
    {}
    double getArea() const override
    {
      return (mDiagWidth * mDiagWidth) / 2;
    }
    rectangle_t getFrameRect() const override
    {
      return rectangle_t {mCenter, mDiagWidth, mDiagWidth};
    }
    void move(point_t newPos) override
    {
      mCenter = newPos;
    }
    void move(double dX, double dY) override
    {
      mCenter.x += dX;
      mCenter.y += dY;
    }
    void scale(double k) override
    {
      mDiagWidth *= k;
    }

  private:
    point_t mCenter;
    double mDiagWidth;
  };

  struct Square : Shape
  {
    Square(point_t center, double width):
      mCenter(center),
      mWidth(width)
    {}
    double getArea() const override
    {
      return mWidth * mWidth;
    }
    rectangle_t getFrameRect() const override
    {
      return rectangle_t {mCenter, mWidth, mWidth};
    }
    void move(point_t newPos) override
    {
      mCenter = newPos;
    }
    void move(double dX, double dY) override
    {
      mCenter.x += dX;
      mCenter.y += dY;
    }
    void scale(double k) override
    {
      mWidth *= k;
    }

  private:
    point_t mCenter;
    double mWidth;
  };

  void scaleShapes(Shape** shapes, size_t shapeCount, point_t base, double k)
  {
    for (size_t i = 0; i < shapeCount; i++)
    {
      Shape* shape = shapes[i];
      point_t pos = shape->getFrameRect().pos;

      double x = (pos.x - base.x) * k + base.x;
      double y = (pos.y - base.y) * k + base.x;
      shape->move({x, y});
      shape->scale(k);
    }
  }

  rectangle_t getFrameRect(Shape** shapes, size_t shapeCount)
  {
    rectangle_t frame = shapes[0]->getFrameRect();

    double minLeft = frame.pos.x - frame.width / 2;
    double maxRight = frame.pos.x + frame.width / 2;
    double maxTop = frame.pos.y + frame.height / 2;
    double minBottom = frame.pos.y - frame.height / 2;

    for (size_t i = 1; i < shapeCount; i++)
    {
      frame = shapes[i]->getFrameRect();

      double left = frame.pos.x - frame.width / 2;
      double right = frame.pos.x + frame.width / 2;
      double top = frame.pos.y + frame.height / 2;
      double bottom = frame.pos.y - frame.height / 2;

      minLeft = std::min(minLeft, left);
      maxRight = std::max(maxRight, right);
      maxTop = std::max(maxTop, top);
      minBottom = std::min(minBottom, bottom);
    }

    double x = (minLeft + maxRight) / 2;
    double y = (minBottom + maxTop) / 2;
    double w = maxRight - minLeft;
    double h = maxTop - minBottom;
    return rectangle_t {{x, y}, w, h};
  }
}

int main()
{
  bukreev::Rectangle rect({0, 0}, 100, 80);
  bukreev::Xquare xqr({20, 30}, 48);
  bukreev::Square sqr({-7, 14}, 20);

  bukreev::Shape* shapes[] = {&rect, &xqr, &sqr};
  bukreev::scaleShapes(shapes, 3, {0, 0}, 1.5f);
}
