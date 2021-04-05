#include "circle.hpp"
#include <cmath>

HalfCircle::HalfCircle(double r, bool positive)
  : GeometricEquation(-r, r, positive?0:-r, positive?r:0)
  , radius2(r*r)
  , dir(positive?1:-1)
{
  // do nothing
}

double HalfCircle::func_raw(double x) const
{
  double y2 = this->radius2 - x*x;
  double y = std::pow(y2, 0.5)*this->dir;

  return y;
}

std::vector<GeometricEquation *> gen_circle(double radius)
{
  std::vector <GeometricEquation *> rv;
  rv.push_back(new HalfCircle(radius, true));
  rv.push_back(new HalfCircle(radius, false));
  return rv;
}
