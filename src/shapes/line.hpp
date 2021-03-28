#pragma once
#include "geometric_equation.hpp"

class Line : public GeometricEquation {
  public:
    Line(double m, double c, double xmin, double xmax);

    double func_raw(double x) const override;

  private:
    double m, c;
};
