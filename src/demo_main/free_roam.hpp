#pragma once
#include "../common/bounce.hpp"
#include "settings.hpp"

#include "player.hpp"

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

        this->fpscntr = new TextRenderable("FPS: ", DEFAULT_FONT, 100);
        this->fpscntr->set_alignment(HA_left, VA_bottom);
        this->fpscntr->set_position({1, 1});
        this->add_floating_renderable(this->fpscntr);
        this->fpscntr->set_parent(cam->get_bl());

        this->pos = new TextRenderable("<pos>", DEFAULT_FONT, 100);
        this->pos->set_alignment(HA_right, VA_bottom);
        this->pos->set_parent(cam->get_br());
        this->add_floating_renderable(this->pos);
    }

    void up() override { this->player->up(); }
    void left() override { this->player->left(); }
    void down() override { this->player->down(); }
    void right() override { this->player->right(); }

    void action() override {}
    void alternate() override {}

    void back() override { this->get_game()->add_event(new PopSceneTransitionEvent()); }

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

    Player *player;
    TextRenderable *fpscntr, *pos;
};
