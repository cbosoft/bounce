#include "rect.hpp"

void RectTransform::set_size(const arma::vec2 &size)
{
    this->_size = size;
}

const arma::vec2 &RectTransform::get_size() const
{
    return this->_size;
}

void RectTransform::set_diagonal_and_aspect(double diagonal, double aspect)
{
    double h = std::sqrt(diagonal*diagonal / (1 + aspect*aspect));
    double w = h*aspect;
    this->set_size({w, h});
}

void RectTransform::set_diagonal_preserve_aspect(double diagonal)
{
    double aspect = this->_size[0] /  this->_size[1];
    this->set_diagonal_and_aspect(diagonal, aspect);
}

void RectTransform::set_aspect_preserve_diagonal(double aspect)
{
    double diagonal = arma::norm(this->_size);
    this->set_diagonal_and_aspect(diagonal, aspect);
}