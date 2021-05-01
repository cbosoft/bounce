#pragma once
#include <bounce/bounce.hpp>

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
        this->player = new DemoPlayer(this, {0, 0});
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

        auto *tut = new TextRenderable("<WASD>: move  <mouse>: aim  <lclick>: shoot  <esc>: back to menu", DEFAULT_FONT, 30);
        tut->set_alignment(HA_right, VA_bottom);
        tut->set_position({-5, 5});
        this->attach_renderable("position counter", tut);
        tut->set_parent(cam->get_br());

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

    void on_activate() override
    {
        Renderer::get().set_screen_effect("crt");
        if (!this->_tut_shown) {
            Game::ref().add_event(new PushSceneTransitionEvent("space shooter tutorial"));
            this->_tut_shown = true;
            this->score_display->hide();
            this->fpscntr->hide();
        }
        else {
            this->score_display->show();
            this->fpscntr->show();
        }
    }

    void up_pressed() override { this->player->up_pressed(); }
    void up_released() override { this->player->up_released(); }
    void left_pressed() override { this->player->left_pressed(); }
    void left_released() override { this->player->left_released(); }
    void down_pressed() override { this->player->down_pressed(); }
    void down_released() override { this->player->down_released(); }
    void right_pressed() override { this->player->right_pressed(); }
    void right_released() override { this->player->right_released(); }

    void action_pressed() override { this->player->shoot(); }
    void action_released() override { this->player->dont_shoot(); }
    void alternate_pressed() override { }

    void back_pressed() override { Game::ref().add_event(new PopSceneTransitionEvent()); }

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
                if (this->_cells.find(tpl) == this->_cells.end()) {
                    arma::vec2 cpos{double(pcx+dx), double(pcy+dy)};
                    cpos *= this->cell_size;
                    auto *cell_centre = new Transform(this, cpos);
                    for (int i = 0; i < 100; i++)
                        this->place_star(cell_centre, this->cell_size * (2. * arma::vec2(arma::fill::randu) - 1.) * 0.5);
                    this->_cells[tpl] = cell_centre;
                }
            }
        }

        for (auto kv : this->_cells) {
            Transform *cell = kv.second;
            double dist = arma::norm(cell->get_position() - p);
            if (dist > this->cell_size*3) {
                if (cell->is_active())
                    cell->deactivate();
            }
            else {
                if (!cell->is_active())
                    cell->activate();
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

        // arma::vec2 at = enemy->get_position() - this->player->get_position();
        // std::cerr << "new enemy dispatched at (" << at[0] << "," << at[1] << ")" << std::endl;
    }

    void on_update() override
    {
        this->update_fps_status();
        const auto &p = this->player->get_position();
        this->update_player_score();
        this->check_update_map(p);
        this->position_reticule();
        this->maybe_dispatch_new_enemy();
    }

private:

    void place_star(Transform *cell, const arma::vec2 &at) {
        auto *star = new DemoStar(cell, at);
        cell->attach_renderable(star);
    }

    bool _tut_shown = false;
    double cell_size = 500.0;
    std::map<std::tuple<int, int>, Transform *> _cells;
    arma::vec2 _cursor_window_position;

    DemoPlayer *player;
    DemoReticule *reticule;
    TextRenderable *fpscntr, *score_display;
};
