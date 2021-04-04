#pragma once
#include <vector>
#include <armadillo>

class GeometricEquation {
  public:
    GeometricEquation(double x_lo, double x_hi, double y_lo, double y_hi);
    double func(double x) const;
    virtual double func_raw(double x) const =0;
    bool intersects(const GeometricEquation& other) const;
    bool intersects(const GeometricEquation& other, arma::vec2 &norm) const;
    bool intersects(const GeometricEquation& other, arma::vec2 &norm, arma::vec2 &at) const;
    std::vector<arma::vec2> as_points(int n = 100);

    arma::vec2 normal_at_point(double x) const;

    double adj_x_lo() const;
    double adj_x_hi() const;
    double adj_y_lo() const;
    double adj_y_hi() const;

    double x_lo, x_hi, y_lo, y_hi;
    arma::vec2 *p;

    void connect_to_next(GeometricEquation *next);
    void connect_to_previous(GeometricEquation *previous);

  private:

    bool in_range_x(double x) const;
    bool in_range_y(double y) const;
    arma::vec2 _self_origin;
    GeometricEquation *_previous, *_next;
};
