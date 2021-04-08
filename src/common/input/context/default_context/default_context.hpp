#pragma once
#include "../context.hpp"
#include "../../../game/game.hpp"

class DefaultContext : public InputContext {
public:
    DefaultContext(Game *game) : InputContext(game) {}

    void left() override { }
    void right() override { }
    void up() override { }
    void down() override { }
    void back() override { this->get_game()->quit(); }

};