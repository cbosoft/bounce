#pragma once

class Game;
class InputContext {
public:
    InputContext(Game *game);

    virtual void up() =0;
    virtual void down() =0;
    virtual void left() =0;
    virtual void right() =0;

    virtual void back() =0;

    // virtual void mouse_position(double x, double y) =0;
    // virtual void left_click() =0;
    // virtual void right_click() =0;

    Game *get_game() const;
private:
    Game *_game;
};