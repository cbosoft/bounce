#include <bounce/transform/rect/rect.hpp>

void RectTransform::set_size(const arma::vec2 &size)
{
    this->_size = size;
    this->_bl->set_relative_position(-size);
    this->_br->set_relative_position(size%arma::vec2{1,-1});
    this->_tl->set_relative_position(size%arma::vec2{-1,1});
    this->_tr->set_relative_position(size);
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

Transform *RectTransform::get_bl()
{
    return this->_bl;
}

Transform *RectTransform::get_br()
{
    return this->_br;
}

Transform *RectTransform::get_tl()
{
    return this->_tl;
}

Transform *RectTransform::get_tr()
{
    return this->_tr;
}
