#include "geometric_equation.hpp"
#include <iostream>

GeometricEquation::GeometricEquation(double x_lo, double x_hi, double y_lo, double y_hi)
  : x_lo(x_lo)
  , x_hi(x_hi)
  , y_lo(y_lo)
  , y_hi(y_hi)
  , _previous(nullptr)
  , _next(nullptr)
{
    // do nothing
}

double GeometricEquation::adj_x_lo() const
{
    return this->get_position()[0] + this->x_lo;
}

double GeometricEquation::adj_x_hi() const
{
    return this->get_position()[0] + this->x_hi;
}

double GeometricEquation::func(double x) const
{
    arma::vec2 pos = this->get_position();
    double xraw = x - pos[0];
    double yraw = this->func_raw(xraw);
    return yraw + pos[1];
}

bool GeometricEquation::intersects(const GeometricEquation &other) const
{
  arma::vec2 dummy;
  return this->intersects(other, dummy);
}

bool GeometricEquation::intersects(const GeometricEquation &other, arma::vec2 &norm) const
{
  arma::vec2 dummy;
  return this->intersects(other, norm, dummy);
}

bool GeometricEquation::intersects(const GeometricEquation &other, arma::vec2 &norm, arma::vec2 &at) const
{

    constexpr double thresh = 5e-3;
    constexpr double m = 0.1;

    arma::vec2 tpos= this->get_position(), opos = other.get_position();

    double tx_lo = this->x_lo + tpos.at(0);
    double tx_hi = this->x_hi + tpos.at(0);
    double ox_lo = other.x_lo + opos.at(0);
    double ox_hi = other.x_hi + opos.at(0);

    if (tx_lo > ox_hi)
        return false;

    double lb = (tx_lo < ox_lo ? ox_lo : tx_lo);
    double ub = (tx_hi > ox_hi ? ox_hi : tx_hi);
    double span = ub - lb;

    if (lb >= ub)
        return false;

    double x = span*0.5 + lb;

    double f = this->func(x) - other.func(x);

    if (f < 0.0) f *= -1.0;

    double dx = span*m;
    for (int i = 0; i < 100; i++) {
        x += dx;
        if (x > ub) x = ub;
        if (x < lb) x = lb;
        double nf = this->func(x) - other.func(x);
        if (nf < 0) nf *= -1.0;
        if ((nf - f) >= 0.0) dx *= -0.5;

        f = nf;

        if (f <= thresh)
          break;

    }

    if (f < thresh) {
        // collision; find normal vector
        auto a = this->normal_at_point(x);
        auto b = other.normal_at_point(x);

        if (a.has_nan() && b.has_nan()) {
          norm = arma::vec2{0,0};
        }
        else if (a.has_nan()) {
          a = b;
        }

        norm = a;
        at = arma::vec2{x, this->func(x)};
        return true;
    }

    return false;
}

// bool GeometricEquation::in_range_x(double x) const
// {
//   double dx = this->p->at(0);
//   double x_lo = this->x_lo + dx, x_hi = this->x_hi + dx;
//   return (x_lo <= x) && (x <= x_hi);
// }
//
// bool GeometricEquation::in_range_y(double y) const
// {
//   double dy = this->p->at(1);
//   double y_lo = this->y_lo + dy, y_hi = this->y_hi + dy;
//   return (y_lo <= y) && (y <= y_hi);
// }

void GeometricEquation::connect_to_next(GeometricEquation *next) { this->_next = next; }
void GeometricEquation::connect_to_previous(GeometricEquation *previous) { this->_previous = previous; }

arma::vec2 GeometricEquation::normal_at_point(double x) const
{
    constexpr double fudge = 1e-2;
    double x_below = x - fudge, x_above = x + fudge;
    double y_below = 0, y_above = 0;

    if (x_below < this->adj_x_lo()) {
        if (this->_previous) {
            y_below = this->_previous->func(x_below);
        }
        else {
            y_below = this->func(this->adj_x_lo());
        }
    }
    else {
        y_below = this->func(x_below);
    }

    if (x_above > this->adj_x_hi()) {
        if (this->_next) {
            y_above = this->_next->func(x_above);
        }
        else {
            y_above = this->func(this->adj_x_hi());
        }
    }
    else {
        y_above = this->func(x_above);
    }

    arma::vec2 rv = arma::normalise(arma::vec2{y_below - y_above, x_above - x_below});
    return rv;
}

std::vector<arma::vec2> GeometricEquation::as_points(int n)
{
  std::vector<arma::vec2> rv;
  double dx = (this->x_hi - this->x_lo) / double(n-1);

  double x = this->x_lo;
  for (int i = 0; i < n; i++) {
    double y = this->func_raw(x);
    rv.emplace_back(arma::vec2{x, y});
    x += dx;
    if (x > this->x_hi) x = x_hi;
  }

  return rv;
}
