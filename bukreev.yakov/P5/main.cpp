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
}

int main()
{}
