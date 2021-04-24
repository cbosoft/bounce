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

    void set_alignment(MeshRenderable_HorizontalAnchor ha, MeshRenderable_VerticalAnchor va);

protected:
    MeshRenderable() =default;

    std::vector<arma::vec2> _points;
    arma::vec2 _anchor;

private:
    void draw_border() const;
    void draw_main() const;

    friend class AnimatedMeshRenderable;
};

class RectangleMeshRenderable : public MeshRenderable {
public:
    RectangleMeshRenderable(double w, double h);
};

class FilletedRectangleMeshRenderable : public MeshRenderable {
public:
    FilletedRectangleMeshRenderable(double w, double h, double r);
};

class RegularPolygonMeshRenderable : public MeshRenderable {
public:
    RegularPolygonMeshRenderable(int n, double theta=M_PI_2);
};

class CircleMeshRenderable : public MeshRenderable {
public:
    CircleMeshRenderable(double radius=0.5);
};