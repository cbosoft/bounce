#pragma once
#include "geometric_equation.hpp"

class Line : public GeometricEquation {
  public:
    Line(double m, double c, double xmin, double xmax);

    double func_raw(double x) const override;
    static Line *from_points(const arma::vec2 &start, const arma::vec2 &end);

  private:
    double m, c;
};
