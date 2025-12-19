namespace bukreev
{
  struct point_t
  {
    double x, y;
  }
  struct rectangle_t
  {
    point_t pos;
    double width, height;
  }

  struct Shape
  {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t newPos) = 0;
    virtual void move(double dX, double dY) = 0;
    virtual void scale(double k) = 0;
  }
}

int main()
{}
