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
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dX, double dY) override;
    void scale(double k) override;

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
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dX, double dY) override;
    void scale(double k) override;

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
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dX, double dY) override;
    void scale(double k) override;

  private:
    point_t mCenter;
    double mWidth;
  };

  void scaleShapes(Shape* const* shapes, size_t shapeCount, point_t base, double k);
  void printShapes(std::ostream& out, const Shape* const* shapes, size_t shapeCount);
  rectangle_t getFrameRect(const Shape* const* shapes, size_t shapeCount);
  void printRectangle(std::ostream& out, rectangle_t rect);
}

int main()
{
  using namespace bukreev;

  Rectangle rect({0, 0}, 100, 80);
  Xquare xqr({20, 30}, 48);
  Square sqr({-7, 14}, 20);
  Shape* shapes[] = {&rect, &xqr, &sqr};

  point_t base;
  double k;

  std::cout << "Enter scaling base: ";
  std::cin >> base.x >> base.y;
  if (!std::cin)
  {
    std::cerr << "Invalid scaling base.\n";
    return 1;
  }

  std::cout << "Enter scaling rate: ";
  std::cin >> k;
  if (!std::cin || k < 0)
  {
    std::cerr << "Invalid scaling rate.\n";
    return 1;
  }

  std::cout << "== BEFORE ==\n";
  printShapes(std::cout, shapes, 3);

  scaleShapes(shapes, 3, base, k);

  std::cout << "== AFTER ==\n";
  printShapes(std::cout, shapes, 3);
}

void bukreev::scaleShapes(Shape* const* shapes, size_t shapeCount, point_t base, double k)
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

void bukreev::printShapes(std::ostream& out, const Shape* const* shapes, size_t shapeCount)
{
  double totalArea = 0;
  for (size_t i = 0; i < shapeCount; i++)
  {
    out << "SHAPE " << i << ":\n";

    double area = shapes[i]->getArea();
    totalArea += area;
    out << "Area: " << area << '\n';
    out << "Frame rect: " << '\n';
    printRectangle(out, shapes[i]->getFrameRect());
    out << '\n';
  }

  out << "Total area: " << totalArea << '\n';
  out << "General frame rect: " << '\n';
  printRectangle(out, getFrameRect(shapes, shapeCount));
  out << '\n';
}

void bukreev::printRectangle(std::ostream& out, rectangle_t rect)
{
  out << " Position: (" << rect.pos.x << ", " << rect.pos.y << ")\n";
  out << " Size: (" << rect.width << ", " << rect.height << ")\n";
}

bukreev::rectangle_t bukreev::getFrameRect(const Shape* const* shapes, size_t shapeCount)
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

double bukreev::Rectangle::getArea() const
{
  return mWidth * mHeight;
}
bukreev::rectangle_t bukreev::Rectangle::getFrameRect() const
{
  return rectangle_t{mCenter, mWidth, mHeight};
}
void bukreev::Rectangle::move(point_t newPos)
{
  mCenter = newPos;
}
void bukreev::Rectangle::move(double dX, double dY)
{
  mCenter.x += dX;
  mCenter.y += dY;
}
void bukreev::Rectangle::scale(double k)
{
  mWidth *= k;
  mHeight *= k;
}

double bukreev::Xquare::getArea() const
{
  return (mDiagWidth * mDiagWidth) / 2;
}
bukreev::rectangle_t bukreev::Xquare::getFrameRect() const
{
  return rectangle_t {mCenter, mDiagWidth, mDiagWidth};
}
void bukreev::Xquare::move(point_t newPos)
{
  mCenter = newPos;
}
void bukreev::Xquare::move(double dX, double dY)
{
  mCenter.x += dX;
  mCenter.y += dY;
}
void bukreev::Xquare::scale(double k)
{
  mDiagWidth *= k;
}

double bukreev::Square::getArea() const
{
  return mWidth * mWidth;
}
bukreev::rectangle_t bukreev::Square::getFrameRect() const
{
  return rectangle_t {mCenter, mWidth, mWidth};
}
void bukreev::Square::move(point_t newPos)
{
  mCenter = newPos;
}
void bukreev::Square::move(double dX, double dY)
{
  mCenter.x += dX;
  mCenter.y += dY;
}
void bukreev::Square::scale(double k)
{
  mWidth *= k;
}
