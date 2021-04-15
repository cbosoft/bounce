#pragma once
#include "../common/bounce.hpp"
#include "settings.hpp"
#include "menu_button.hpp"

class MainMenu final: public Menu {
public:
    explicit MainMenu(Game *game)
            : Menu(game, "menu")
    {
        {
            auto *b = new MenuButton(this, "physics sim");
            b->set_position({50, 15});
            this->add_item(b);
            b->set_callback_action(MainMenu::sim_callback);
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

        // draw logo
        {
            auto *ttl = new Object(this, {-60, 10});
            ttl->set_renderable(new TextRenderable("Bounce", DEFAULT_FONT, 150));
            ttl->set_colour(Colour::from_grayscale(40));
            ttl->set_layer("title 1");
            this->add_object(ttl);
            auto *brk = new Object(this, {-60, 0}, true);
            brk->set_layer("title 1");
            this->add_object(brk);
        }
        {
            auto *ttl = new Object(this, {-55, 5});
            ttl->set_renderable(new TextRenderable("Bounce", DEFAULT_FONT, 175));
            ttl->set_colour(Colour::from_grayscale(127));
            ttl->set_layer("title 2");
            this->add_object(ttl);
            auto *brk = new Object(this, {-55, -5}, true);
            brk->set_layer("title 2");
            this->add_object(brk);
        }
        {
            auto *ttl = new Object(this, {-50, 0});
            ttl->set_renderable(new TextRenderable("Bounce", DEFAULT_FONT, 200));
            ttl->set_colour(Colour::from_grayscale(255));
            ttl->set_layer("title 3");
            this->add_object(ttl);
            auto *brk = new Object(this, {-50, -10}, true);
            brk->set_layer("title 3");
            this->add_object(brk);
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

    void back() override { this->get_game()->quit(); };
};
