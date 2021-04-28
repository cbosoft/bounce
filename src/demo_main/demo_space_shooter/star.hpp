#pragma once
#include "../../engine/bounce.hpp"

class DemoStar final: public RegularPolygonMeshRenderable {
public:
    DemoStar(Transform *parent, const arma::vec2 &position)
            : RegularPolygonMeshRenderable(50)
    {
        this->set_parent(parent);
        this->set_relative_position(position);
        this->set_z(-300);
        this->set_texture_name("star");
        double s = 0.5 + std::abs(arma::randn()*3);
        this->set_size({s, s});
        constexpr double max_sat = 0.5;
        this->_saturation = arma::randu()*max_sat;
        this->_hue = arma::randu();
    }

    void on_update() override
    {
        double time = PhysicsEngine::ref().get_time();
        constexpr double min_brightness = 0.7;
        double brightness = (std::sin(time*0.1) + 1.0)*0.5*(1.0 - min_brightness) + min_brightness;
        this->set_colour(Colour::from_hsv_f(this->_hue, this->_saturation, brightness));
    }

private:
    double _saturation, _hue;
};
