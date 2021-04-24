#pragma once
#include "../engine/bounce.hpp"
#include "settings.hpp"

#include "player.hpp"

class Star final: public RegularPolygonMeshRenderable {
public:
    Star(Transform *parent, const arma::vec2 &position)
    : RegularPolygonMeshRenderable(50)
    {
        this->set_parent(parent);
        this->set_position(position);
        this->set_shader_name("star");
        this->set_z(-100);
        double s = 0.5 + std::abs(arma::randn()*3);
        this->set_size({s, s});
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

class Bar : public BarGraph {
public:
    explicit Bar(Player *player)
    :  BarGraph(30, 5)
    ,   _player(player)
    {
        this->set_alignment(MR_HA_LEFT, MR_VA_TOP);
        this->set_border_size(0.1);
        this->set_colour(Colours::black);
        this->set_z(100);
    }
    double measure_value() const override { return this->_player->get_ammo_left(); }
    double measure_maximum() const override { return 1.0; }
private:
    Player *_player;
};


class Cursor final: public RegularPolygonMeshRenderable {
public:
    explicit Cursor(Transform *parent)
    : RegularPolygonMeshRenderable(50)
    {
        this->set_parent(parent);
        this->set_size({5.0, 5.0});
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
        this->_cursor_window_position = Renderer::get().get_window_size()%arma::vec2{.5,-.5};

        this->fpscntr = new TextRenderable("FPS: ", DEFAULT_FONT, 100);
        this->fpscntr->set_alignment(HA_left, VA_bottom);
        this->fpscntr->set_position({1, 1});
        this->attach_renderable("FPS counter", this->fpscntr);
        this->fpscntr->set_parent(cam->get_bl());

        this->pos = new TextRenderable("<pos>", DEFAULT_FONT, 100);
        this->pos->set_alignment(HA_right, VA_bottom);
        this->attach_renderable("position counter", this->pos);
        this->pos->set_parent(cam->get_br());

        // this->hud = new AnimatedMeshRenderable(new RectangleMeshRenderable(1, 1));
        // this->hud_big = new RectangleMeshRenderable(20, 2);
        // this->attach_renderable(hud);
        // this->hud->set_parent(this->player);
        // this->hud->set_relative_position({10, 10});
        // this->hud->set_alignment(MR_HA_LEFT, MR_VA_BOTTOM);
        // this->hud->hide();

        this->ammo_counter = new Bar(this->player);
        this->attach_renderable(this->ammo_counter);
        this->ammo_counter->set_parent(cam->get_tl());
        this->ammo_counter->set_relative_position({5, -5});
    }

    void up() override { this->player->up(); }
    void left() override { this->player->left(); }
    void down() override { this->player->down(); }
    void right() override { this->player->right(); }

    void action() override { this->player->shoot(); this->show_hud(); }
    void alternate() override { this->show_hud(); }

    void back() override { this->get_game()->add_event(new PopSceneTransitionEvent()); }

    void cursor_position(const arma::vec2 &p) override
    {
        this->_cursor_window_position = p;
    }

    void update_fps_status()
    {
        std::stringstream ss;
        ss << "FPS: " << Renderer::get().get_fps();
        std::string s = ss.str();
        this->fpscntr->set_text(s);
    }

    void update_player_pos_vel(const arma::vec2 &p)
    {
        const auto &v = this->player->get_velocity();
        std::stringstream ss;
        ss << int(p[0]) << "." << int(p[1]) << ">>" << int(v[0]) << "." << int(v[1]);
        std::string s = ss.str();
        this->pos->set_text(s);
    }

    void check_update_map(const arma::vec2 &p)
    {
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

    void show_hud()
    {
        //this->hud->animate_to(this->hud_big, 10);
        this->frames_until_hide = 100;
        this->ammo_counter->show();
    }

    void hide_hud()
    {
        //this->hud->animate_to_original(20);
        this->ammo_counter->hide();
    }

    void check_hide_hud()
    {
        if (!this->frames_until_hide) {
            this->hide_hud();
        }
        else {
            this->frames_until_hide--;
        }
    }

    void position_cursor()
    {
        arma::vec2 wrld = Renderer::get().screen_pos_to_world_pos(this->_cursor_window_position);
        this->cursor->set_position(wrld);
        const arma::vec2 &d = wrld - this->player->get_position();
        double len = arma::norm(d);
        double angle = std::acos(d[0]/len);
        if (d[1] < 0.0) angle = -angle;
        this->player->aim(angle);
    }

    void on_update() override
    {
        this->update_fps_status();
        const auto &p = this->player->get_position();
        this->update_player_pos_vel(p);
        this->check_update_map(p);
        this->check_hide_hud();
        this->position_cursor();
    }

private:

    void place_star(const arma::vec2 &at) {
        auto *star = new Star(this, at);
        this->attach_renderable(star);
    }

    double cell_size = 500.0;
    std::map<std::tuple<int, int>, bool> _cell_generated;
    arma::vec2 _cursor_window_position;

    Player *player;
    Cursor *cursor;
    TextRenderable *fpscntr, *pos;
    // AnimatedMeshRenderable *hud;
    // MeshRenderable *hud_big;
    Bar *ammo_counter;
    int frames_until_hide = 0;
};
