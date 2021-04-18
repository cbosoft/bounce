#pragma once

#include <vector>
#include <armadillo>
#include "../renderable.hpp"

class MeshRenderable : public Renderable {
public:
    explicit MeshRenderable(const std::vector<arma::vec2> &points);

    void draw() const override;

    static MeshRenderable *rectangle(double w, double h);
    static MeshRenderable *filleted_rectangle(double w, double h, double r);
    static MeshRenderable *regular_polygon(int n, double angle=M_PI_2);

private:

    std::vector<arma::vec2> points;

    friend class AnimatedMeshRenderable;
};