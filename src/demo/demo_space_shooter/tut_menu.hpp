#pragma once

#include <bounce/bounce.hpp>
#include "../settings.hpp"

class DemoSpaceShooterTutorialMenu final : public Menu {
public:
    DemoSpaceShooterTutorialMenu()
    : Menu("space shooter tutorial")
    {
        this->_insubstantial = true;
        auto *note1 = new TextRenderable("You are being pursued.", DEFAULT_FONT, 110);
        note1->set_position({0, 10});
        this->attach_renderable(note1);

        auto *note2 = new TextRenderable("Survive as long as you can!", DEFAULT_FONT, 100);
        note2->set_position({0, -10});
        this->attach_renderable(note2);

        auto *note3 = new TextRenderable("<esc>", DEFAULT_FONT, 70);
        note3->set_position({0, -40});
        this->attach_renderable(note3);
    }

    void back_pressed() override
    {
        Game::ref().pop_active_scene();
    }
};