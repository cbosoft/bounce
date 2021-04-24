#pragma once

#include "../../renderer/renderable/mesh/mesh.hpp"

class BarGraph : public RectangleMeshRenderable {
public:
    explicit BarGraph(double w, double h);

    void draw() const override;

protected:
    virtual double measure_value() const = 0;
    virtual double measure_maximum() const = 0;

private:
    double _value;
};