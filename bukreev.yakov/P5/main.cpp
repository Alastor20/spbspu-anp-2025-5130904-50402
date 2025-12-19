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
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(point_t newPos);
    virtual void move(double dX, double dY);
    virtual void scale(double k);
  }
}

int main()
{}
