#include "line.hpp"

Line::Line(double m, double c, double xmin, double xmax)
  : GeometricEquation(xmin, xmax, xmin*m+c, xmax*m+c)
  , m(m)
  , c(c)
{
  // do nothing
}

Line *Line::from_points(const arma::vec2 &start, const arma::vec2 &end)
{
  auto dir = end - start;
  double m = dir[0] == 0.0 ? 1e9 : dir[1]/dir[0];
  double c = start[1] - m*start[0];

  double xmin, xmax;
  double a = (start[1] - c)/m, b = (end[1] - c)/m;
  if (a < b) {
    xmin = a; xmax = b;
  }
  else {
    xmin = b; xmax = a;
  }

  std::cerr
    << m << " "
    << c << " "
    << xmin << " "
    << xmax << " "
    << std::endl;

  return new Line(m, c, xmin, xmax);
}

double Line::func_raw(double x) const
{
  double y = x*this->m + this->c;
  return y;
}
