#include <vector>
#include "geometric_equation.hpp"


class HalfCircle : public GeometricEquation {
  public:
    HalfCircle(double r, bool positive);

    double func(double x) const override;

    double radius2, dir;
};

std::vector <GeometricEquation *> gen_circle(double radius);
