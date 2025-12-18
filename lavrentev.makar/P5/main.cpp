#include <cmath>
#include <iostream>
#include <new>
#include <stdexcept>

namespace lavrentev {
const size_t n = 3;

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
  explicit Rectangle(const r_t dd);

  Rectangle(const Rectangle &dd) = default;
  Rectangle &operator=(const Rectangle &dd) = default;
  Rectangle &operator=(Rectangle &&dd) = default;
  Rectangle(Rectangle &&dd) = default;
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
  explicit Rubber(const ru_t dd);

  Rubber(const Rubber &dd) = default;
  Rubber &operator=(const Rubber &dd) = default;
  Rubber &operator=(Rubber &&dd) = default;
  Rubber(Rubber &&dd) = default;
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
  explicit Polygon(const pol_t dd);

  Polygon(const Polygon &dd) = default;
  Polygon &operator=(const Polygon &dd) = default;
  Polygon &operator=(Polygon &&dd) = default;
  Polygon(Polygon &&dd) = default;
  ~Polygon() = default;

  double getArea() const override;
  lavrentev::r_t getFrameRect() const override;
  void move(const lavrentev::p_t &c) override;
  void move(double d_x, double d_y) override;
  void scale(double coef) override;
};

int polyPos(pol_t &pol);
lavrentev::r_t fullFrame(lavrentev::Shape *const *figures, size_t n);
void userShape(lavrentev::Shape *figures, p_t user_dot, double coef);
} // namespace lavrentev

int main() {

  lavrentev::r_t re;
  re.height = 5;
  re.width = 8;
  re.pos = {3, 3};

  lavrentev::ru_t ru;
  ru.pos = {-7, -2};
  ru.rPos = 3.5;
  ru.outCenter = {-5, 0};
  ru.rOut = 9;

  lavrentev::pol_t pol;
  pol.n = 7;
  lavrentev::p_t *vrtxs = nullptr;
  try {
    vrtxs = new lavrentev::p_t[pol.n]{{1.2, 5.6},   {3.3, -4.7},  {1.1, 9.3},
                                      {-5.5, -3.0}, {-7.3, -0.3}, {-2.1, 4.8},
                                      {3.6, 8.3}};
  } catch (std::bad_alloc &e) {
    std::cerr << "Memory allocation failed: " << e.what() << '\n';
    delete[] vrtxs;
    return 1;
  }

  pol.vertexes = vrtxs;

  int k = polyPos(pol);
  if (k == 1) {
    std::cerr << "Polygon not exists";
  }

  lavrentev::Shape *figures[lavrentev::n] = {};
  try {
    figures[0] = new lavrentev::Rectangle(re);
    figures[1] = new lavrentev::Rubber(ru);
    figures[2] = new lavrentev::Polygon(pol);
  } catch (...) {
    delete figures[0];
    delete figures[1];
    delete figures[2];
  }

  double x, y, coef;
  std::cin >> x >> y >> coef;
  if (std::cin.fail()) {
    std::cerr << "Invalid input" << '\n';
    return 1;
  }
  if (coef <= 0) {
    std::cerr << "Incorrect ratio" << '\n';
    return 1;
  }
  lavrentev::p_t user_dot = {x, y};

  std::cout << "Площадь Rectangle: " << figures[0]->getArea() << '\n';
  std::cout << "Площадь Rubber: " << figures[1]->getArea() << '\n';
  std::cout << "Площадь Polygon " << figures[2]->getArea() << '\n';
  std::cout << "Суммарная площадь: "
            << figures[0]->getArea() + figures[1]->getArea() +
                   figures[2]->getArea()
            << "\n\n";

  lavrentev::r_t rg = figures[0]->getFrameRect();
  std::cout << "Ограничивающий прямоугольник Rectangle:" << '\n';
  std::cout << '\t' << "Центр: {" << rg.pos.x << ", " << rg.pos.y << '}'
            << '\n';
  std::cout << '\t' << "Длина: " << rg.width << '\n';
  std::cout << '\t' << "Высота: " << rg.height << '\n';

  lavrentev::r_t rug = figures[1]->getFrameRect();
  std::cout << "Ограничивающий прямоугольник Rubber:" << '\n';
  std::cout << '\t' << "Центр: {" << rug.pos.x << ", " << rug.pos.y << '}'
            << '\n';
  std::cout << '\t' << "Длина: " << rug.width << '\n';
  std::cout << '\t' << "Высота: " << rug.height << '\n';

  lavrentev::r_t pg = figures[2]->getFrameRect();
  std::cout << "Ограничивающий прямоугольник Polygon:" << '\n';
  std::cout << '\t' << "Центр: {" << pg.pos.x << ", " << pg.pos.y << '}'
            << '\n';
  std::cout << '\t' << "Длина: " << pg.width << '\n';
  std::cout << '\t' << "Высота: " << pg.height << "\n\n";

  lavrentev::r_t ff = lavrentev::fullFrame(figures, lavrentev::n);
  std::cout << "Общий ограничивающий прямоугольник:" << '\n';
  std::cout << '\t' << "Центр: {" << ff.pos.x << ", " << ff.pos.y << '}'
            << '\n';
  std::cout << '\t' << "Длина: " << ff.width << '\n';
  std::cout << '\t' << "Высота: " << ff.height << "\n\n";

  lavrentev::userShape(*figures, user_dot, coef);

  std::cout << "Новые данные: " << "\n\n";
  std::cout << "Площадь Rectangle: " << figures[0]->getArea() << '\n';
  std::cout << "Площадь Rubber: " << figures[1]->getArea() << '\n';
  std::cout << "Площадь Polygon " << figures[2]->getArea() << '\n';
  std::cout << "Суммарная площадь: "
            << figures[0]->getArea() + figures[1]->getArea() +
                   figures[2]->getArea()
            << "\n\n";

  rg = figures[0]->getFrameRect();
  std::cout << "Ограничивающий прямоугольник Rectangle:" << '\n';
  std::cout << '\t' << "Центр: {" << rg.pos.x << ", " << rg.pos.y << '}'
            << '\n';
  std::cout << '\t' << "Длина: " << rg.width << '\n';
  std::cout << '\t' << "Высота: " << rg.height << '\n';

  rug = figures[1]->getFrameRect();
  std::cout << "Ограничивающий прямоугольник Rubber:" << '\n';
  std::cout << '\t' << "Центр: {" << rug.pos.x << ", " << rug.pos.y << '}'
            << '\n';
  std::cout << '\t' << "Длина: " << rug.width << '\n';
  std::cout << '\t' << "Высота: " << rug.height << '\n';

  pg = figures[2]->getFrameRect();
  std::cout << "Ограничивающий прямоугольник Polygon:" << '\n';
  std::cout << '\t' << "Центр: {" << pg.pos.x << ", " << pg.pos.y << '}'
            << '\n';
  std::cout << '\t' << "Длина: " << pg.width << '\n';
  std::cout << '\t' << "Высота: " << pg.height << "\n\n";

  ff = lavrentev::fullFrame(figures, lavrentev::n);
  std::cout << "Общий ограничивающий прямоугольник:" << '\n';
  std::cout << '\t' << "Центр: {" << ff.pos.x << ", " << ff.pos.y << '}'
            << '\n';
  std::cout << '\t' << "Длина: " << ff.width << '\n';
  std::cout << '\t' << "Высота: " << ff.height << "\n\n";

  delete figures[0];
  delete figures[1];
  delete figures[2];
  delete[] vrtxs;
}

lavrentev::Rectangle::Rectangle(const r_t dd) : data(dd) {
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

lavrentev::Rubber::Rubber(const ru_t dd) : data(dd) {
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

lavrentev::Polygon::Polygon(const pol_t dd) : data(dd) {
  if (dd.n <= 2) {
    throw std::invalid_argument("Invalid amount of vertexes");
  }
}

double lavrentev::Polygon::getArea() const {
  double buf1 = 0.0, buf2 = 0.0, s = 0.0;
  for (size_t i = 0; i < data.n - 1; ++i) {
    buf1 += (data.vertexes[i].x * data.vertexes[i + 1].y);
    buf2 += (data.vertexes[i].y * data.vertexes[i + 1].x);
  }
  buf1 += data.vertexes[data.n - 1].x * data.vertexes[0].y;
  buf2 += data.vertexes[data.n - 1].y * data.vertexes[0].x;
  s = 0.5 * abs(buf1 - buf2);
  return s;
}

lavrentev::r_t lavrentev::Polygon::getFrameRect() const {
  p_t l_u = data.vertexes[0], r_b = data.vertexes[0];
  for (size_t i = 0; i < data.n; ++i) {
    if (data.vertexes[i].x < l_u.x) {
      l_u.x = data.vertexes[i].x;
    }
    if (data.vertexes[i].y > l_u.y) {
      l_u.y = data.vertexes[i].y;
    }
    if (data.vertexes[i].x > r_b.x) {
      r_b.x = data.vertexes[i].x;
    }
    if (data.vertexes[i].y < r_b.y) {
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

void lavrentev::Polygon::move(const lavrentev::p_t &c) { data.pos = c; }

void lavrentev::Polygon::move(double d_x, double d_y) {
  data.pos.x += d_x;
  data.pos.y += d_y;
}

void lavrentev::Polygon::scale(double coef) {
  if (coef <= 0) {
    throw std::invalid_argument("Coef must be positive");
  }
  for (size_t i = 0; i < data.n; ++i) {
    double d_x = data.vertexes[i].x - data.pos.x;
    double d_y = data.vertexes[i].y - data.pos.y;
    d_x *= coef;
    d_y *= coef;
    data.vertexes[i].x = data.pos.x + d_x;
    data.vertexes[i].y = data.pos.y + d_y;
  }
}

int lavrentev::polyPos(lavrentev::pol_t &pol) {
  if (pol.n < 3) {
    return 1;
  }

  double square = 0.0;
  for (size_t i = 0; i < pol.n; ++i) {
    size_t j = (i + 1) % pol.n;
    square += (pol.vertexes[i].x * pol.vertexes[j].y) -
              (pol.vertexes[j].x * pol.vertexes[i].y);
  }
  square *= 0.5;

  if (square != 0.0) {
    double c_x = 0.0;
    for (size_t i = 0; i < pol.n; ++i) {
      size_t j = (i + 1) % pol.n;
      c_x += (pol.vertexes[i].x + pol.vertexes[j].x) *
             (pol.vertexes[i].x * pol.vertexes[j].y -
              pol.vertexes[j].x * pol.vertexes[i].y);
    }
    c_x /= (6 * square);

    double c_y = 0.0;
    for (size_t i = 0; i < pol.n; ++i) {
      size_t j = (i + 1) % pol.n;
      c_y += (pol.vertexes[i].y + pol.vertexes[j].y) *
             (pol.vertexes[i].x * pol.vertexes[j].y -
              pol.vertexes[j].x * pol.vertexes[i].y);
    }
    c_y /= (6 * square);
    pol.pos.x = c_x;
    pol.pos.y = c_y;
  } else {
    return 1;
  }
  return 0;
}

lavrentev::r_t lavrentev::fullFrame(lavrentev::Shape *const *figures,
                                    size_t n) {
  double left = 0.0, right = 0.0, up = 0.0, down = 0.0;
  for (size_t i = 0; i < n; ++i) {
    lavrentev::r_t buf = figures[i]->getFrameRect();
    if (buf.pos.x - buf.width * 0.5 < left) {
      left = buf.pos.x - buf.width * 0.5;
    }
    if (buf.pos.x + buf.width * 0.5 > right) {
      right = buf.pos.x + buf.width * 0.5;
    }
    if (buf.pos.y - buf.height * 0.5 < down) {
      down = buf.pos.y - buf.height * 0.5;
    }
    if (buf.pos.y + buf.height * 0.5 > up) {
      up = buf.pos.y + buf.height * 0.5;
    }
  }
  lavrentev::r_t ff;
  ff.height = up - down;
  ff.width = right - left;
  ff.pos.y = (up + down) * 0.5;
  ff.pos.x = (right + left) * 0.5;
  return ff;
}

void lavrentev::userShape(lavrentev::Shape *figures, p_t user_dot,
                          double coef) {
  (void)figures;
  (void)user_dot;
  (void)coef;
}
