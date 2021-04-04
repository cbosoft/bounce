#include <cmath>

#include "polygon.hpp"
#include "line.hpp"

// Generate a regular polygon of $n sides, circumscribed by circle with $radius
std::vector<GeometricEquation *> gen_regular_polygon(double radius, int n)
{
    double dtheta = M_PI*2.0/double(n), theta=0.0;
    std::vector<arma::vec2> points;
    for (int i = 0; i < n; i++) {
        double x = radius*std::cos(theta);
        double y = radius*std::sin(theta);
        points.emplace_back(arma::vec2{x, y});
        theta += dtheta;
    }

    std::vector<GeometricEquation *> rv;
    for (int i = 0; i < n; i++) {
        int j = (i+1) % n;
        rv.emplace_back(Line::from_points(points[i], points[j]));
    }

    for (int i = 0; i < n; i++) {
        int prev = i == 0 ? n-1 : i-1;
        int next = i == (n-1) ? 0 : i+1;
        rv[i]->connect_to_previous(rv[prev]);
        rv[i]->connect_to_next(rv[next]);
    }

    return rv;
}
