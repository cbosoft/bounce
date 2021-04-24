#pragma once

#include "../engine/bounce.hpp"
#include "settings.hpp"

class Boid final: public Object {
public:
    explicit Boid(Scene *parent, const arma::vec2 &position, double search_radius)
            : Object(parent, position, false)
            , _scene(parent)
            , _search_radius(search_radius)
            , _max_velocity(5.0)
    {
        double theta = M_2_PI * arma::randu();
        this->set_velocity( {this->_max_velocity*std::cos(theta), this->_max_velocity*std::sin(theta)} );
        this->attach_renderable("circle", new RegularPolygonMeshRenderable(20));
        this->set_radius(0.5);
        this->set_layer("boids");
    }

    void on_update() override {
        std::vector<Object *> nearby = this->_scene->find_objects_near_to(this, this->_search_radius);
        if (nearby.empty())
            return;

        arma::vec2 f_sep, pos = this->get_position(), tot{0.0, 0.0};
        double n = 0.0;
        for (auto *obj : nearby) {
            if (obj == this)
                continue;
            if (obj->get_layer() != this->get_layer())
                continue;
            // separation - change direction to avoid collisions
            arma::vec2 dr = (obj->get_position() - pos);
            f_sep -= dr;
            tot += obj->get_velocity();
            n += 1.0;
        }
        this->set_force(f_sep);

        if (n >= 1.0) {
            // alignment - align velocity with nearby
            // cohesion - head for the centre of mass of boids
            arma::vec2 av = tot / n;
            //const double split = 0.9;
            //av = av*(1.0 - split) + this->get_velocity()*split;

            // av = av - 0.0001*this->get_position();
            //if (arma::norm(av) > this->_max_velocity)
            //    av  = this->_max_velocity*arma::normalise(av);
            this->set_velocity(av);
        }

        // bounds
        const double size = 100, hsize = size/2.;
        double x = pos[0], y = pos[1];
        if (x > hsize)  x -= size;
        if (x < -hsize) x += size;
        if (y > hsize)  y -= size;
        if (y < -hsize) y += size;
        this->set_position({x, y});
    }
private:
    Scene *_scene;
    double _search_radius, _max_velocity;
};
