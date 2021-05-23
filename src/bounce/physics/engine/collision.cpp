#include <bounce/physics/engine/engine.hpp>
#include <bounce/logging/logger.hpp>

bool PhysicsEngine::check_will_collide(const Rigidbody *a, const Rigidbody *b, CollisionInformation &ci) const
{
    if (a->is_fixed() && b->is_fixed()) {
        return false;
    }

    arma::vec2 dv = arma::abs(a->get_velocity() - b->get_velocity());
    ci.normal = dv[1] > dv[0] ? arma::vec2{0, 1} : arma::vec2{1, 0};

    // std::cerr
    //     << a->get_shape().get_type() << " " << b->get_shape().get_type()
    //     << a->get_position()[0] << "," << a->get_position()[1] << " "
    //     << b->get_position()[0] << "," << b->get_position()[1] << " "
    //     << std::endl;

    switch (a->get_shape_type()) {
        case ST_CIRCLE:
            switch (b->get_shape_type()) {
                case ST_CIRCLE:
                    return this->check_will_collide_circle_circle(a, b, ci);
                case ST_RECT:
                    return this->check_will_collide_circle_rect(a, b, ci);
            }
            break;
        case ST_RECT:
            switch (b->get_shape_type()) {
                case ST_CIRCLE:
                    return this->check_will_collide_circle_rect(b, a, ci);
                case ST_RECT:
                    return this->check_will_collide_rect_rect(a, b, ci);
            }
            break;
    }

    return false;
}

bool PhysicsEngine::check_will_collide_circle_circle(const Rigidbody *a, const Rigidbody *b, CollisionInformation &ci) const
{
    arma::vec2 dp = a->get_position() - b->get_position();
    arma::vec2 dv = a->get_velocity() - b->get_velocity();
    double ar, br;
    a->get_circle_radius(ar);
    b->get_circle_radius(br);
    double l = arma::norm(dp) - (ar + br);
    double v = arma::norm(dv);
    double t = l/v;
    ci.normal = arma::normalise(dv);
    ci.at = a->get_position() + ci.normal*ar;
    ci.when = t;
    return t < this->get_dt();

    // arma::vec2 dp = a->get_new_position() - b->get_new_position();
    // double dist = arma::norm(dp);
    // double tdist = (a->get_shape().w + b->get_shape().w)*.5;
    // if (dist <= tdist) {
    //     return true;
    // }

    // return false;
}

bool PhysicsEngine::check_will_collide_circle_rect(const Rigidbody *a, const Rigidbody *b, CollisionInformation &ci) const
{
    (void) a;
    (void) b;
    (void) ci;
    return false;
}

bool PhysicsEngine::check_will_collide_rect_rect(const Rigidbody *a, const Rigidbody *b, CollisionInformation &ci) const
{
    const arma::vec2 &apos = a->get_position();
    const arma::vec2 &bpos = b->get_position();
    double ahw, ahh, bhw, bhh;
    a->get_rect_half_extents(ahw, ahh);
    b->get_rect_half_extents(bhw, bhh);
    double ax = apos[0], ay = apos[1], bx = bpos[0], by = bpos[1];
    arma::vec2 rel_vel = b->get_velocity() - a->get_velocity();
    arma::vec2 &uray = rel_vel; //arma::normalise(rel_vel);
    double df_x = 1./uray[0], df_y = 1./uray[1];

    double h_ww = ahw + bhw;
    double h_hh = ahh + bhh;

    double l = ax - h_ww, r = ax+h_ww;
    double B = ay - h_hh, t = ay+h_hh;

    double t2left   = (l - bx)*df_x;
    double t2right  = (r - bx)*df_x;
    double t2bottom = (B - by)*df_y;
    double t2top    = (t - by)*df_y;

    double tmin = std::max(std::min(t2left, t2right), std::min(t2bottom, t2top));
    double tmax = std::min(std::max(t2left, t2right), std::max(t2bottom, t2top));

    if (tmax < 0. || tmin > tmax)
        return false;

    if (tmin == t2left) {
        ci.normal = {-1, 0};
        ci.adir = CD_LEFT;
        ci.bdir = CD_RIGHT;
    }
    else if (tmin == t2right) {
        ci.normal = {1, 0};
        ci.adir = CD_RIGHT;
        ci.bdir = CD_LEFT;
    }
    else if (tmin == t2bottom) {
        ci.normal = {0, -1};
        ci.adir = CD_BOTTOM;
        ci.bdir = CD_TOP;
    }
    else if (tmin == t2top) {
        ci.normal = {0, 1};
        ci.adir = CD_TOP;
        ci.bdir = CD_BOTTOM;
    }

    ci.when = tmin;

    return tmin < this->dt;
}