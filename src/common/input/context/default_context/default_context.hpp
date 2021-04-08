#pragma once
#include "../context.hpp"
#include "../../../game/game.hpp"

class DefaultContext : public InputContext {
public:
    DefaultContext(Game *game) : InputContext(game) {}

    static constexpr double speed = 1e3;
    void left() override  { this->get_game()->get_player()->add_force({ -speed,    0.0}); }
    void right() override { this->get_game()->get_player()->add_force({  speed,    0.0}); }
    void up() override    { this->get_game()->get_player()->add_force({    0.0,  speed}); }
    void down() override  { this->get_game()->get_player()->add_force({    0.0, -speed}); }
    void back() override { this->get_game()->quit(); }

};