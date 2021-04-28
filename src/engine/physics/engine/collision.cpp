#include "engine.hpp"

bool PhysicsEngine::check_will_collide(const Object *a, const Object *b, arma::vec2 &normal, arma::vec2 &at)
{
    if (a->shape.is_circle()) {
        if (b->shape.is_circle()) {
            return this->check_will_collide_circle_circle(a, b, normal, at);
        }
        else if (b->shape.is_rectangle()) {
            return this->check_will_collide_circle_rect(a, b, normal, at);
        }
        else {
            throw std::runtime_error("unrecognised shape - did you forget to update physics after adding a new shape?");
        }
    }
    else if (a->shape.is_rectangle()) {
        if (b->shape.is_circle()) {
            return this->check_will_collide_circle_rect(b, a, normal, at);
        }
        else if (b->shape.is_rectangle()) {
            return this->check_will_collide_rect_rect(a, b, normal, at);
        }
        else {
            throw std::runtime_error("unrecognised shape - did you forget to update physics after adding a new shape?");
        }
    }
    else {
        throw std::runtime_error("unrecognised shape - did you forget to update physics after adding a new shape?");
    }
}

bool PhysicsEngine::check_will_collide_circle_circle(const Object *a, const Object *b, arma::vec2 &normal, arma::vec2 &at)
{
    arma::vec2 dp = a->get_new_position() - b->get_new_position();
    double dist = arma::norm(dp);
    double tdist = a->shape.w + b->shape.w;
    if (dist <= tdist) {
        normal = arma::normalise(dp);
        at = a->get_position() + normal*a->shape.w;
        return true;
    }

    return false;
}

bool PhysicsEngine::check_will_collide_circle_rect(const Object *a, const Object *b, arma::vec2 &normal, arma::vec2 &at)
{
    (void) a;
    (void) b;
    (void) normal;
    (void) at;
    return false;
}

bool PhysicsEngine::check_will_collide_rect_rect(const Object *a, const Object *b, arma::vec2 &normal, arma::vec2 &at)
{
    (void) a;
    (void) b;
    (void) normal;
    (void) at;
    return false;
}
