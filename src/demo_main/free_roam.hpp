#pragma once
#include "../common/bounce.hpp"
#include "settings.hpp"

#include "player.hpp"

class Star final: public CircleRenderable {
public:
    Star(Transform *parent, const arma::vec2 &position)
    :   CircleRenderable()
    {
        this->set_parent(parent);
        this->set_position(position);
        this->set_shader_name("star");
        this->set_z(-1);
        this->set_scale(0.5 + arma::randu()*3);
        constexpr double max_sat = 0.5;
        this->_saturation = arma::randu()*max_sat;
        this->_hue = arma::randu();
    }

    // void update() override
    // {
    //     double time = PhysicsEngine::engine().get_time();
    //     constexpr double min_brightness = 0.7;
    //     double brightness = (std::sin(time*0.1) + 1.0)*0.5*(1.0 - min_brightness) + min_brightness;
    //     this->set_colour(Colour::from_hsv_f(this->_hue, this->_saturation, brightness));
    // }

private:
    double _saturation, _hue;
};

class Cursor final: public CircleRenderable {
public:
    Cursor(Transform *parent)
    : CircleRenderable()
    {
        this->set_parent(parent);
    }
};

class FreeRoamScene final: public Scene {
public:
    explicit FreeRoamScene(Game *game)
            : Scene(game, "free roam")
            , player(nullptr)
    {
        auto *o = new Object(this, {0, 0}, false);
        o->set_radius(10.0);
        o->set_renderable(MeshRenderable::rectangle(10, 5));
        o->set_layer("other");
        this->add_object(o);

        o = new Object(this, {0, 0}, false, 0.5);
        o->set_radius(4.0);
        o->set_colour(Colours::gray);
        o->set_renderable(MeshRenderable::regular_polygon(5));
        this->add_object(o);

        this->player = new Player(this, {30, 0});
        this->player->set_radius(4.0);
        this->player->set_colour(Colours::blue);
        this->player->set_renderable(new CircleRenderable());
        this->add_object(this->player);
        auto *cam = this->get_active_camera();
        cam->set_parent(this->player);

        this->cursor = new Cursor(this);
        this->add_floating_renderable(this->cursor);

        this->fpscntr = new TextRenderable("FPS: ", DEFAULT_FONT, 100);
        this->fpscntr->set_alignment(HA_left, VA_bottom);
        this->fpscntr->set_position({1, 1});
        this->add_floating_renderable(this->fpscntr);
        this->fpscntr->set_parent(cam->get_bl());

        this->pos = new TextRenderable("<pos>", DEFAULT_FONT, 100);
        this->pos->set_alignment(HA_right, VA_bottom);
        this->pos->set_parent(cam->get_br());
        this->add_floating_renderable(this->pos);

        for (int i = 0; i < 100; i++)
            this->place_star(200 * (2.*arma::vec2(arma::fill::randu) - 1.));
    }

    void up() override { this->player->up(); }
    void left() override { this->player->left(); }
    void down() override { this->player->down(); }
    void right() override { this->player->right(); }

    void action() override {}
    void alternate() override {}

    void back() override { this->get_game()->add_event(new PopSceneTransitionEvent()); }

    void mouse_position(double x, double y) override
    {
        arma::vec2 wrld = Renderer::get().screen_pos_to_world_pos({x, y});
        this->cursor->set_position(wrld);
    }

    void on_update() override
    {
        std::stringstream ss;
        ss << "FPS: " << Renderer::get().get_fps();
        std::string s = ss.str();
        this->fpscntr->set_text(s);

        const auto &p = this->player->get_position();
        const auto &v = this->player->get_velocity();
        ss.str("");
        ss << int(p[0]) << "." << int(p[1]) << ">>" << int(v[0]) << "." << int(v[1]);
        s = ss.str();
        this->pos->set_text(s);
    }

private:

    void place_star(const arma::vec2 &at) {
        auto *star = new Star(this, at);
        this->add_floating_renderable(star);
    }

    Player *player;
    Cursor *cursor;
    TextRenderable *fpscntr, *pos;
};
