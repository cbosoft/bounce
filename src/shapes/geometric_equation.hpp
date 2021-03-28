#pragma once
#include <vector>
#include <armadillo>

class GeometricEquation {
  public:
    GeometricEquation(double x_lo, double x_hi, double y_lo, double y_hi);
    double func(double x) const;
    virtual double func_raw(double x) const =0;
    bool intersects(const GeometricEquation& other, arma::vec2 &norm) const;
    std::vector<arma::vec2> as_points(int n = 100);

    arma::vec2 normal_at_point(double x) const;

    double x_lo, x_hi, y_lo, y_hi;
    arma::vec2 *p;

  private:

    bool in_range_x(double x) const;
    bool in_range_y(double y) const;

    // int points_n;
    // std::vector<arma::vec2> points;
};
