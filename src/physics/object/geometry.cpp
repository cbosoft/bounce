#include "object.hpp"

void PhysicsObject::add_geometry(GeometricEquation *eqn)
{
    if (eqn == nullptr)
        return;

    eqn->p = &this->new_position;
    this->eqns.push_back(eqn);
}

void PhysicsObject::add_geometry(const std::vector<GeometricEquation *> &_eqns)
{
    for (auto *eqn : _eqns) {
        this->add_geometry(eqn);
    }
}

std::vector<std::vector<arma::vec2>> PhysicsObject::get_lines()
{
    if (this->_cached_eqn_points.empty()) {
        int i = 0;
        for (auto *eqn: this->eqns) {
            this->_cached_eqn_points.emplace_back(std::vector<arma::vec2>());
            for (const auto &pt: eqn->as_points()) {
                this->_cached_eqn_points[i].emplace_back(pt);
            }
            i++;
        }
    }

    std::vector<std::vector<arma::vec2>> rv;
    int i = 0;
    for (const auto &list : this->_cached_eqn_points) {
        rv.emplace_back(std::vector<arma::vec2>());
        for (const auto &pt : list) {
            rv[i].emplace_back(pt + this->position);
        }
        i++;
    }
    return rv;
}
