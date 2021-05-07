#pragma once

#include <bounce/bounce.hpp>
#include "../settings.hpp"

class DemoSpaceShooterEndGameMenu : public Menu {
public:
    DemoSpaceShooterEndGameMenu()
    :   Menu("shooter end game")
    {
        this->_insubstantial = true;

        auto *txt = new TextRenderable("Game Over", DEFAULT_FONT, 100);
        txt->set_colour(Colours::red);
        this->attach_renderable(txt);
    }

    void back_pressed() override
    {
        Game::ref().add_event(new PopSceneTransitionEvent());
        Game::ref().add_event(new PopSceneTransitionEvent());
        Game::ref().add_event(new PushSceneTransitionEvent("menu"));
    }
};