#include "renderable.hpp"

void Renderable::add_geometry(GeometricEquation *eqn)
{
    this->_shape.emplace_back(eqn);
    eqn->set_parent(this);
}

void Renderable::add_geometry(const std::vector<GeometricEquation *> &eqns)
{
    for (const auto &eqn: eqns) {
        this->_shape.emplace_back(eqn);
        eqn->set_parent(this);
    }
}

std::vector<std::vector<arma::vec2>> Renderable::get_lines()
{
    if (this->_cached_lines.empty() || this->cache_invalid()) {
        int i = 0;
        for (auto *eqn: this->_shape) {
            this->_cached_lines.emplace_back(std::vector<arma::vec2>());
            for (const auto &pt: eqn->as_points()) {
                this->_cached_lines[i].emplace_back(pt);
            }
            i++;
        }
    }

    std::vector<std::vector<arma::vec2>> rv;
    int i = 0;
    for (const auto &list : this->_cached_lines) {
        rv.emplace_back(std::vector<arma::vec2>());
        for (const auto &pt : list) {
            rv[i].emplace_back(pt + this->get_position());
        }
        i++;
    }
    return rv;
}
