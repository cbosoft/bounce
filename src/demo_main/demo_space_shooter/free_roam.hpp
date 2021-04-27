#pragma once
#include "../../engine/bounce.hpp"
#include "../settings.hpp"

#include "player.hpp"
#include "star.hpp"
#include "enemy.hpp"
#include "reticule.hpp"


class DemoSpaceShooter final: public Scene {
public:
    DemoSpaceShooter()
            : Scene("demo space shooter")
    {
        this->player = new DemoPlayer(this, {30, 0});
        auto *cam = this->get_active_camera();
        cam->set_parent(this->player);

        this->reticule = new DemoReticule(this);
        this->reticule->set_position({10, 0});
        this->attach_renderable(this->reticule);
        this->_cursor_window_position = Renderer::get().get_window_size()%arma::vec2{.5,-.5};

        this->fpscntr = new TextRenderable("FPS: ", DEFAULT_FONT, 100);
        this->fpscntr->set_alignment(HA_left, VA_bottom);
        this->fpscntr->set_position({5, 5});
        this->attach_renderable("FPS counter", this->fpscntr);
        this->fpscntr->set_parent(cam->get_bl());

        this->pos = new TextRenderable("<pos>", DEFAULT_FONT, 100);
        this->pos->set_alignment(HA_right, VA_bottom);
        this->pos->set_position({-5, 5});
        this->attach_renderable("position counter", this->pos);
        this->pos->set_parent(cam->get_br());

        auto *bg = new RectangleMeshRenderable(400, 400);
        bg->set_colour(Colour::from_rgb(0, 0, 30));
        bg->set_z(-1000);
        this->attach_renderable(bg);
        bg->set_parent(cam);

        this->score_display = new TextRenderable("0", DEFAULT_FONT, 150);
        this->score_display->set_alignment(HA_centre, VA_top);
        this->attach_renderable(this->score_display);
        this->score_display->set_parent(cam);
        this->score_display->set_relative_position({0, 70});

        auto *enemy = new DemoEnemy(this, {100, 100}, this->player);
        (void) enemy;
    }

    void up() override { this->player->up(); }
    void left() override { this->player->left(); }
    void down() override { this->player->down(); }
    void right() override { this->player->right(); }

    void action() override { this->player->shoot(); }
    void alternate() override { }

    void back() override { Game::ref().add_event(new PopSceneTransitionEvent()); }

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

    void update_player_score()
    {
        long score = this->player->get_score();
        std::stringstream ss;
        ss << score;
        std::string s = ss.str();
        this->score_display->set_text(s);
        if (score < 0) this->score_display->set_colour(Colours::red);
        else this->score_display->set_colour(Colours::blue);
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

    void position_reticule()
    {
        arma::vec2 wrld = Renderer::get().screen_pos_to_world_pos(this->_cursor_window_position);
        this->reticule->set_position(wrld);

        const arma::vec2 &d = wrld - this->player->get_position();
        double len = arma::norm(d);
        double angle = std::acos(d[0]/len);
        if (d[1] < 0.0) angle = -angle;
        this->player->aim(angle);
    }

    void maybe_dispatch_new_enemy()
    {
        if (arma::randu() > 1e-2)
            return;
        auto *enemy = new DemoEnemy(this, {100, 100}, this->player);

        // while (true) {
        arma::vec2 quadrant(arma::fill::randu), dist(arma::fill::randu);
        quadrant[0] = quadrant[0] < 0.5 ? -1. : 1.;
        quadrant[1] = quadrant[1] < 0.5 ? -1. : 1.;
        dist *= 0.5;
        dist += 0.5;
        dist *= 100.;
        arma::vec2 p = dist%quadrant;
        enemy->set_position(this->player->get_position() + p);
        //     auto close_objects = this->find_objects_near_to(enemy, 10);
        //     if (close_objects.empty())
        //         break;
        // };

        arma::vec2 at = enemy->get_position() - this->player->get_position();
        std::cerr << "new enemy dispatched at (" << at[0] << "," << at[1] << ")" << std::endl;
    }

    void on_update() override
    {
        this->update_fps_status();
        const auto &p = this->player->get_position();
        this->update_player_pos_vel(p);
        this->update_player_score();
        this->check_update_map(p);
        this->position_reticule();
        this->maybe_dispatch_new_enemy();
    }

private:

    void place_star(const arma::vec2 &at) {
        auto *star = new DemoStar(this, at);
        this->attach_renderable(star);
    }

    double cell_size = 500.0;
    std::map<std::tuple<int, int>, bool> _cell_generated;
    arma::vec2 _cursor_window_position;

    DemoPlayer *player;
    DemoReticule *reticule;
    TextRenderable *fpscntr, *pos, *score_display;
};