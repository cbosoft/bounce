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

class Enemy : public Object {
public:
    Enemy(Transform *parent, const arma::vec2 &position, Player *target)
    :   Object(parent, position, 1.0)
    ,   evasive_mult(1.0)
    ,   _target(target)
    {
        this->body = new RegularPolygonMeshRenderable(20);
        body->set_colour(Colour::from_rgb(255, 225, 225));
        body->set_texture_name("enemy");
        body->set_size({5, 5});
        this->set_radius(2.5);
        this->attach_renderable(body);
    }

    void face_forward()
    {
        arma::vec2 vd = arma::normalise(this->get_velocity());
        double len = arma::norm(vd);
        if (len > 0.0) {
            double angle = std::acos(vd[0] / len);
            if (vd[1] < 0.0) angle *= -1.0;
            this->body->set_angle(angle);
        }
    }

    void head_toward_target()
    {
        auto dp = this->_target->get_position() - this->get_position();
        arma::vec2 f = arma::normalise(dp)*5e3;
        this->set_force(f);
    }

    void enforce_max_vel()
    {
        auto v = this->get_velocity();
        double vm = arma::norm(v);
        constexpr double MAX_VEL = 50.0;
        if (vm > MAX_VEL) {
            auto nv = arma::normalise(v);
            this->set_velocity(MAX_VEL*nv);
        }
    }

    void maybe_change_state()
    {
        if (arma::randu() < 1./60.) {
            this->_state = ENEMY_EVASIVE;
            this->cooldown = 10;
            if (arma::randu() < 0.1)
                this->evasive_mult *= -1.0;
        }
    }

    void evasive_manoeuvre()
    {
        if (this->cooldown-- > 0) {
            auto dp = this->_target->get_position() - this->get_position();
            arma::vec2 perp{-dp[1], dp[0]};
            arma::vec2 f = arma::normalise(perp)*5e3*this->evasive_mult;
            this->set_force(f);
        }
        else {
            this->_state = ENEMY_ATTACKING;
        }
    }

    void on_update() override
    {
        switch (this->_state) {
            case ENEMY_ATTACKING:
                this->head_toward_target();
                this->maybe_change_state();
                break;

            case ENEMY_EVASIVE:
                this->evasive_manoeuvre();
                break;
        }

        this->face_forward();
        this->enforce_max_vel();
    }

    void on_collision(Object *other) override
    {
        if ((Transform *)other == (Transform *)this->_target) {
            this->_target->damage(1.0);
        }
        else {
            this->_target->score(10.0);
            Game::ref().add_event(new TransformDestroyEvent(this));
        }
        Game::ref().add_event(new TemporaryTimePause(10));
    }

private:
    enum AI_STATE { ENEMY_ATTACKING, ENEMY_EVASIVE };
    AI_STATE _state = ENEMY_ATTACKING;
    int cooldown = 0;
    double evasive_mult;
    Player *_target;
    MeshRenderable *body;
};

class Bar : public BarGraph {
public:
    explicit Bar(Player *player)
    :  BarGraph(30, 5)
    ,   _player(player)
    {
        this->set_alignment(MR_HA_LEFT, MR_VA_TOP);
        this->set_position({5, -5});
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
    FreeRoamScene()
            : Scene("free roam")
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

        // auto *bg = new RectangleMeshRenderable(2048, 2048);
        // this->attach_renderable(bg);
        // bg->set_texture_name("noise1");
        // bg->set_z(10);

        auto *enemy = new Enemy(this, {100, 100}, this->player);
        (void) enemy;
    }

    void up() override { this->player->up(); }
    void left() override { this->player->left(); }
    void down() override { this->player->down(); }
    void right() override { this->player->right(); }

    void action() override { this->player->shoot(); this->show_hud(); }
    void alternate() override { this->show_hud(); }

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

    void maybe_dispatch_new_enemy()
    {
        if (arma::randu() > 1e-2)
            return;
        auto *enemy = new Enemy(this, {100, 100}, this->player);
        (void)enemy;

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
        this->check_update_map(p);
        // this->check_hide_hud();
        this->position_cursor();
        this->maybe_dispatch_new_enemy();
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
