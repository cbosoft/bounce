#include "line.hpp"

Line::Line(double m, double c, double xmin, double xmax)
  : GeometricEquation(xmin, xmax, xmin*m+c, xmax*m+c)
  , m(m)
  , c(c)
{
  // do nothing
}

double Line::func_raw(double x) const
{
  double y = x*this->m + this->c;
  return y;
}
