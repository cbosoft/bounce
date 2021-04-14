#pragma once

#include "../transform.hpp"

class RectTransform : public Transform {
public:
    RectTransform(Transform *parent, const arma::vec2 &size);

    void set_diagonal_preserve_aspect(double diagonal);
    void set_aspect_preserve_diagonal(double aspect);
    void set_diagonal_and_aspect(double diagonal, double aspect);
    void set_size(const arma::vec2 &size);
    const arma::vec2 &get_size() const;

private:
    arma::vec2 _size;
};