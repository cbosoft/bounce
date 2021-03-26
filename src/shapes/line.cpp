#include "line.hpp"

Line::Line(double m, double c, double xmin, double xmax)
  : GeometricEquation(xmin, xmax, xmin*m+c, xmax*m+c)
  , m(m)
  , c(c)
{
  // do nothing
}

double Line::func(double x) const
{
  x -= this->p->at(0);
  double y = x*this->m + this->c;
  y += this->p->at(1);
  return y;
}
