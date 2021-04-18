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
        this->set_scale(0.5 + std::abs(arma::randn()*3));
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
        this->set_scale(3.0);
        this->set_z(100);
        this->set_texture_name("crosshair");
    }
};

class FreeRoamScene final: public Scene {
public:
    explicit FreeRoamScene(Game *game)
            : Scene(game, "free roam")
    {
        this->player = new Player(this, {30, 0});
        auto *cam = this->get_active_camera();
        cam->set_parent(this->player);

        // auto *bg = MeshRenderable::rectangle(200, 200);
        // bg->set_shader_name("starfield");
        // this->add_floating_renderable(bg);
        // bg->set_parent(this->player);
        // bg->set_z(-100);

        this->cursor = new Cursor(this);
        this->cursor->set_position({10, 0});
        this->attach_renderable("cursor", this->cursor);

        this->fpscntr = new TextRenderable("FPS: ", DEFAULT_FONT, 100);
        this->fpscntr->set_alignment(HA_left, VA_bottom);
        this->fpscntr->set_position({1, 1});
        this->attach_renderable("FPS counter", this->fpscntr);
        this->fpscntr->set_parent(cam->get_bl());

        this->pos = new TextRenderable("<pos>", DEFAULT_FONT, 100);
        this->pos->set_alignment(HA_right, VA_bottom);
        this->attach_renderable("position counter", this->pos);
        this->pos->set_parent(cam->get_br());

    }

    void up() override { this->player->up(); }
    void left() override { this->player->left(); }
    void down() override { this->player->down(); }
    void right() override { this->player->right(); }

    void action() override {this->player->shoot(); }
    void alternate() override {}

    void back() override { this->get_game()->add_event(new PopSceneTransitionEvent()); }

    void cursor_position(const arma::vec2 &pos) override
    {
        arma::vec2 wrld = Renderer::get().screen_pos_to_world_pos(pos);
        this->cursor->set_position(wrld);
        const arma::vec2 &d = wrld - this->player->get_position();
        double len = arma::norm(d);
        double angle = std::acos(d[0]/len);
        if (d[1] < 0.0) angle = -angle;
        this->player->aim(angle);
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

        int pcx = std::floor(p[0]/this->cell_size + 0.5);
        int pcy = std::floor(p[1]/this->cell_size + 0.5);
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                auto tpl = std::make_tuple(pcx+dx, pcy+dy);
                if (this->_cell_generated.find(tpl) == this->_cell_generated.end()) {
                    arma::vec2 cell_centre{double(pcx+dx), double(pcy+dy)};
                    cell_centre *= this->cell_size;
                    for (int i = 0; i < 100; i++)
                        this->place_star(
                                cell_centre + this->cell_size * (2. * arma::vec2(arma::fill::randu) - 1.) * 0.5);
                    this->_cell_generated[tpl] = true;
                }
            }
        }
    }

private:

    void place_star(const arma::vec2 &at) {
        auto *star = new Star(this, at);
        this->attach_renderable(star);
    }

    double cell_size = 500.0;
    std::map<std::tuple<int, int>, bool> _cell_generated;

    Player *player;
    Cursor *cursor;
    TextRenderable *fpscntr, *pos;
};
