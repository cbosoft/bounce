#pragma once

#include <vector>
#include <armadillo>
#include "../renderable.hpp"

enum MeshRenderable_HorizontalAnchor {MR_HA_CENTRE, MR_HA_LEFT, MR_HA_RIGHT};
enum MeshRenderable_VerticalAnchor {MR_VA_CENTRE, MR_VA_TOP, MR_VA_BOTTOM};

class MeshRenderable : public Renderable {
public:
    explicit MeshRenderable(const std::vector<arma::vec2> &points);

    void draw() const override;

    static MeshRenderable *rectangle(double w, double h);
    static MeshRenderable *filleted_rectangle(double w, double h, double r);
    static MeshRenderable *regular_polygon(int n, double angle=M_PI_2);

    void set_alignment(MeshRenderable_HorizontalAnchor ha, MeshRenderable_VerticalAnchor va);

private:

    std::vector<arma::vec2> points;
    arma::vec2 _anchor;

    friend class AnimatedMeshRenderable;
};