#include <cmath>
#include <iostream>
#include <stdexcept>

namespace lavrentev {
struct p_t {
  double x, y;
};

struct r_t {
  double width, height;
  p_t pos;
};

struct ru_t {
  p_t pos;
  p_t outCenter;
  double rPos;
  double rOut;
};

struct pol_t {
  p_t pos;
  size_t n;
  p_t *vertexes;
};

struct Shape {
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual r_t getFrameRect() const = 0;
  virtual void move(const p_t &c) = 0;
  virtual void move(double d_x, double d_y) = 0;
  virtual void scale(double coef) = 0;
};

struct Rectangle : Shape {
private:
  r_t data;
public:
  explicit Rectangle(const r_t &dd);

  Rectangle(const Rectangle& dd) = default;
  Rectangle& operator=(const Rectangle& dd) = default;
  Rectangle& operator=(Rectangle&& dd) = default;
  Rectangle(Rectangle&& dd) = default;
  ~Rectangle() = default;

  double getArea() const override;
  lavrentev::r_t getFrameRect() const override;
  void move(const lavrentev::p_t &c) override;
  void move(double d_x, double d_y) override;
  void scale(double coef) override;
};

struct Rubber : Shape {
private:
  ru_t data;

public:
  explicit Rubber(const ru_t &dd);

  Rubber(const Rubber& dd) = default;
  Rubber& operator=(const Rubber& dd) = default;
  Rubber& operator=(Rubber&& dd) = default;
  Rubber(Rubber&& dd) = default;
  ~Rubber() = default;

  double getArea() const override;
  lavrentev::r_t getFrameRect() const override;
  void move(const lavrentev::p_t &c) override;
  void move(double d_x, double d_y) override;
  void scale(double coef) override;
};

struct Polygon : Shape {
private:
  pol_t data;

public:
  explicit Polygon(const pol_t &dd);

  Polygon(const Polygon& dd) = default;
  Polygon& operator=(const Polygon& dd) = default;
  Polygon& operator=(Polygon&& dd) = default;
  Polygon(Polygon&& dd) = default;
  ~Polygon() = default;

  double getArea() const override;
  lavrentev::r_t getFrameRect() const override;
  void move(const lavrentev::p_t &c) override;
  void move(double d_x, double d_y) override;
  void scale(double coef) override;
};
}

int main() {}

lavrentev::Rectangle::Rectangle(const r_t &dd) : data(dd) {
  if (dd.width <= 0 || dd.height <= 0) {
    throw std::invalid_argument("Invalid weight or height");
  }
}

double lavrentev::Rectangle::getArea() const {
  return data.width * data.height;
}

lavrentev::r_t lavrentev::Rectangle::getFrameRect() const { return data; }

void lavrentev::Rectangle::move(const lavrentev::p_t &c) { data.pos = c; }

void lavrentev::Rectangle::move(double d_x, double d_y) {
  data.pos.x += d_x;
  data.pos.y += d_y;
}

void lavrentev::Rectangle::scale(double coef) {
  if (coef <= 0) {
    throw std::invalid_argument("Coef must be positive");
  }
  data.width *= coef;
  data.height *= coef;
}

lavrentev::Rubber::Rubber(const ru_t &dd) : data(dd) {
  if (dd.rOut <= 0 || dd.rPos <= 0) {
    throw std::invalid_argument("Invalid value of radius");
  }
}

double lavrentev::Rubber::getArea() const {
  return M_PI * data.rOut * data.rOut - M_PI * data.rPos * data.rPos;
}

lavrentev::r_t lavrentev::Rubber::getFrameRect() const {
  lavrentev::r_t ans;
  ans.pos = data.outCenter;
  ans.height = data.rOut * 2;
  ans.width = data.rOut * 2;
  return ans;
}

void lavrentev::Rubber::move(const lavrentev::p_t &c) { data.pos = c; }

void lavrentev::Rubber::move(double d_x, double d_y) {
  data.pos.x += d_x;
  data.pos.y += d_y;
}

void lavrentev::Rubber::scale(double coef) {
  if (coef <= 0) {
    throw std::invalid_argument("Coef must be positive");
  }
  data.rPos *= coef;
  data.rOut *= coef;
}

lavrentev::Polygon::Polygon(const pol_t &dd) : data(dd) {
  if (dd.n <= 2) {
    throw std::invalid_argument("Invalid amount of vertexes");
  }
}

double lavrentev::Polygon::getArea() const {
  double buf1, buf2, s = 0;
  size_t i = 0;
  while(i < data.n) {
    buf1 += (data.vertexes[i].x * data.vertexes[i + 1].y);
    buf2 += (data.vertexes[i].y * data.vertexes[i + 1].x);
    ++i;
  }
  buf1 += (data.vertexes[i].x * data.vertexes[0].y);
  buf2 += (data.vertexes[i].y * data.vertexes[0].x);
  s = 0.5 * abs(buf1 - buf2);
  return s;
}

lavrentev::r_t lavrentev::Polygon::getFrameRect() const {
  p_t l_u, r_b;
  for(size_t i = 0; i < data.n; ++i) {
    if (data.vertexes[i].x < l_u.x)
    {
      l_u.x = data.vertexes[i].x;
    }
    if (data.vertexes[i].y > l_u.y)
    {
      l_u.y = data.vertexes[i].y;
    }
    if (data.vertexes[i].x > r_b.x)
    {
      r_b.x = data.vertexes[i].x;
    }
    if (data.vertexes[i].y < r_b.y)
    {
      r_b.y = data.vertexes[i].y;
    }
  }
  r_t ans;
  double w = r_b.x - l_u.x;
  double h = l_u.y - r_b.y;
  p_t p;
  p.x = (r_b.x + l_u.x) * 0.5;
  p.y = (r_b.y + l_u.y) * 0.5;
  ans.pos = p;
  ans.width = w;
  ans.height = h;
  return ans;
}

void lavrentev::Polygon::move(const lavrentev::p_t &c)
{
    data.pos = c;
}

void lavrentev::Polygon::move(double d_x, double d_y) {
  data.pos.x += d_x;
  data.pos.y += d_y;
}

void lavrentev::Polygon::scale(double coef) {
  if (coef <= 0) {
    throw std::invalid_argument("Coef must be positive");
  }
  for(size_t i = 0; i < data.n; ++i)
  {
    double d_x = data.vertexes[i].x - data.pos.x;
    double d_y = data.vertexes[i].y - data.pos.y;
    d_x *= coef;
    d_y *= coef;
    data.vertexes[i].x = d_x - data.pos.x;
    data.vertexes[i].y = d_y - data.pos.y;
  }
}
