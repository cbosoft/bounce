#pragma once

#include <armadillo>

class Transform {
public:
    Transform();
    Transform(Transform *parent);

    const arma::vec2 &relative_position() const;
    arma::vec2 position() const;

    void relative_position(const arma::vec2 &relative_position);
    void position(const arma::vec2 &position);

    void parent(Transform *parent);
    Transform *parent() const;

private:
    Transform *_parent;
    arma::vec2 _relative_position;
};