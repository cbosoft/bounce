#pragma once
#include "../engine/bounce.hpp"
#include "settings.hpp"
#include "menu_button.hpp"

class MenuCursor final: public AnimatedMeshRenderable {
public:
    explicit MenuCursor(Transform *parent)
            : AnimatedMeshRenderable(new RegularPolygonMeshRenderable(20))
    {
        this->set_parent(parent);
        this->set_z(-100);
    }
};

class MenuAnimLogo final : public RectangleMeshRenderable {
public:
    explicit MenuAnimLogo(Transform *parent)
        :   RectangleMeshRenderable(48, 8)
        ,   _speed(10)
        ,   _countdown(_speed)
    {
        this->set_parent(parent);
        this->set_z(-100);
        this->set_texture_name("anim-test-logo");
        this->_current_texture_loop = this->_texture->get_named_loop("loop");
        this->set_angle(M_PI_2);
    }

    void on_update() override
    {
        if (!this->_countdown--) {
            TextureFrameCoords tc = this->_texture->get_texcoords_of_frame(this->_current_frame);
            this->_current_frame++;
            if (this->_current_frame > this->_current_texture_loop.to) {
                this->_current_frame = this->_current_texture_loop.from;
            }
            this->_countdown = this->_speed;
        }
    }

private:
    int _speed, _countdown;
};

class MainMenu final: public Menu {
public:
    explicit MainMenu(Game *game)
            :   Menu(game, "menu")
            //,   _px(0)
            //,   _py(0)
    {
        {
            auto *b = new MenuButton(this, "physics sim");
            b->set_position({50, 15});
            this->add_item(b);
            b->set_callback_action(MainMenu::sim_callback);
            std::cerr << b->get_position() << std::endl;
        }
        {
            auto *b = new MenuButton(this, "free roam");
            b->set_position({50, 0});
            this->add_item(b);
            b->set_callback_action(MainMenu::free_roam_callback);
        }
        {
            auto *b = new MenuButton(this, "quit");
            b->set_position({50, -15});
            this->add_item(b);
            b->set_callback_action(MainMenu::quit_callback);
        }

        this->connect_vertical();

        this->cursor = new MenuCursor(this);
        this->cursor->set_position({10, 0});
        this->attach_renderable("cursor", this->cursor);

        // draw logo
        {
            auto *ttl = new Object(this, {-60, 10});
            ttl->attach_renderable("bounce1", new TextRenderable("Bounce", DEFAULT_FONT, 150));
            ttl->set_colour(Colour::from_grayscale(40));
            ttl->set_layer("title 1");
            auto *brk = new Object(this, {-60, 0}, true);
            brk->set_layer("title 1");
        }
        {
            auto *ttl = new Object(this, {-55, 5});
            ttl->attach_renderable("bounce2", new TextRenderable("Bounce", DEFAULT_FONT, 175));
            ttl->set_colour(Colour::from_grayscale(127));
            ttl->set_layer("title 2");
            auto *brk = new Object(this, {-55, -5}, true);
            brk->set_layer("title 2");
        }
        {
            auto *ttl = new Object(this, {-50, 0});
            ttl->attach_renderable("bounce3", new TextRenderable("Bounce", DEFAULT_FONT, 200));
            ttl->set_colour(Colour::from_grayscale(255));
            ttl->set_layer("title 3");
            auto *brk = new Object(this, {-50, -10}, true);
            brk->set_layer("title 3");
        }
        {
            auto *anim_logo = new MenuAnimLogo(this);
            this->attach_renderable(anim_logo);
        }

        auto *gravity = new UnboundedLinearForceField(0, 0, 0, -10);
        this->add_field(gravity);
    }

    static void quit_callback(MenuItem *i)
    {
        i->get_game()->quit();
    }

    static void sim_callback(MenuItem *i)
    {
        i->get_game()->add_event(new PushSceneTransitionEvent("sim"));
    }

    static void free_roam_callback(MenuItem *i)
    {
        i->get_game()->add_event(new PushSceneTransitionEvent("free roam"));
    }

    void cursor_position(const arma::vec2 &p) override
    {
        arma::vec2 wrld = Renderer::get().screen_pos_to_world_pos(p);
        this->cursor->set_position(wrld);
    }

    void on_update() override
    {
        for (MenuItem *item : this->get_items()) {
            auto *btn = (MenuButton *)item;
            if (btn->is_near(this->cursor, 5.0)) {
                this->cursor->animate_to(btn->bg, 10);
                this->cursor->set_position(btn->get_position());
                this->set_selected(btn);
                return;
            }
        }

        this->cursor->animate_to_original(5);
    }

    // void cursor_position(const arma::vec2 &pos) override
    // {
    //     double x = pos[0], y = pos[1];
    //     double dx = x - this->_px;
    //     if (std::abs(dx) > 100) {
    //         if (dx > 0.0) this->right();
    //         else this->left();

    //         this->_px = x;
    //     }

    //     double dy = y - this->_py;
    //     if (std::abs(dy) > 100) {
    //         if (dy > 0.0) this->down();
    //         else this->up();

    //         this->_py = y;
    //     }
    // }

    void back() override { this->get_game()->quit(); };

    void alternate() override {
        static MeshRenderable *other = new RegularPolygonMeshRenderable(10, 10);
        static bool doobeedoo = false;
        std::cerr << "CALLED " << doobeedoo << std::endl;

        if (doobeedoo) {
            this->cursor->animate_to(other, 100);
        }
        else {
            this->cursor->animate_to_original(100);
        }

        doobeedoo = !doobeedoo;
    }

private:
    //double _px, _py;
    MenuCursor *cursor;
};
