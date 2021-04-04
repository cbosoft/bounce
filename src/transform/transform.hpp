#pragma once

#include <armadillo>

class Transform {
public:
    Transform();
    Transform(Transform *parent);
    Transform(Transform *parent, const arma::vec2 &position);

    const arma::vec2 &get_relative_position() const;
    arma::vec2 get_position() const;

    void set_relative_position(const arma::vec2 &relative_position);
    void set_position(const arma::vec2 &position);

    void set_parent(Transform *parent);
    Transform *get_parent() const;

private:
    Transform *_parent;
    arma::vec2 _relative_position;
};