#include <bounce/physics/engine/engine.hpp>

bool PhysicsEngine::check_will_collide(const Object *a, const Object *b, arma::vec2 &normal, arma::vec2 &at)
{
    arma::vec2 dv = arma::abs(a->get_velocity() - b->get_velocity());
    normal = dv[1] > dv[0] ? arma::vec2{0, 1} : arma::vec2{1, 0};

    // std::cerr
    //     << a->get_shape().get_type() << " " << b->get_shape().get_type()
    //     << a->get_position()[0] << "," << a->get_position()[1] << " "
    //     << b->get_position()[0] << "," << b->get_position()[1] << " "
    //     << std::endl;

    switch (a->get_shape().get_type()) {
        case ST_CIRCLE:
            switch (b->get_shape().get_type()) {
                case ST_CIRCLE:
                    return this->check_will_collide_circle_circle(a, b, normal, at);
                case ST_RECT:
                    return this->check_will_collide_circle_rect(a, b, normal, at);
            }
            break;
        case ST_RECT:
            switch (b->get_shape().get_type()) {
                case ST_CIRCLE:
                    return this->check_will_collide_circle_rect(b, a, normal, at);
                case ST_RECT:
                    return this->check_will_collide_rect_rect(a, b, normal, at);
            }
            break;
    }
}

bool PhysicsEngine::check_will_collide_circle_circle(const Object *a, const Object *b, arma::vec2 &normal, arma::vec2 &at)
{
    arma::vec2 dp = a->get_new_position() - b->get_new_position();
    double dist = arma::norm(dp);
    double tdist = (a->get_shape().w + b->get_shape().w)*.5;
    if (dist <= tdist) {
        normal = arma::normalise(dp);
        at = a->get_position() + normal*a->get_shape().w*.5;
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

bool pt_in_rect(const arma::vec2 &pt, const arma::vec2 &c, double w, double h, arma::vec2 &normal)
{
    const double hw = w*0.5, hh = h*0.5;
    const double left = c[0] - hw, right = c[0] + hw;
    const double bottom = c[1] - hh, top = c[1] + hh;
    const double x = pt[0], y = pt[1];

    constexpr double thresh = 1e-1;
    if ((left <= x) && (x <= right) && (bottom <= y) && (y <= top)) {
        if (std::abs(y - top) < thresh) {
            normal = {0, 1};
        }
        else if (std::abs(y - bottom) < thresh) {
            normal = {0, -1};
        }
        else if (std::abs(x - left) < thresh) {
            normal = {1, 0};
        }
        else if (std::abs(x - right) < thresh) {
            normal = {-1, 0};
        }
        return true;
    }
    return false;
}

void get_rect_corners(std::list<arma::vec2> &out, const arma::vec2 &c, double w, double h)
{
    double hw = w*0.5, hh = h*0.5;
    double left = c[0] - hw, right = c[0] + hw;
    double bottom = c[1] - hh, top = c[1] + hh;
    out = {
            {left, top},
            {right, top},
            {right, bottom},
            {left, bottom},
    };
}


bool PhysicsEngine::check_will_collide_rect_rect(const Object *a, const Object *b, arma::vec2 &normal, arma::vec2 &at)
{
    const arma::vec2 &apos = a->get_new_position();
    const arma::vec2 &bpos = b->get_new_position();
    double aw = a->get_shape().w, ah = a->get_shape().h;
    double bw = b->get_shape().w, bh = b->get_shape().h;

    std::list<arma::vec2> corners;
    get_rect_corners(corners, apos, aw, ah);

    for (const auto &corner : corners) {
        if (pt_in_rect(corner, bpos, bw, bh, normal)) {
            at = corner;
            return true;
        }
    }

    // corners.clear();
    // get_rect_corners(corners, bpos, bw, bh);

    // for (const auto &corner : corners) {
    //     if (pt_in_rect(corner, apos, aw, ah, normal)) {
    //         at = corner;
    //         return true;
    //     }
    // }

    return false;
}
