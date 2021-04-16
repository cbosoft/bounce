#pragma once

class Game;
class InputContext {
public:
    explicit InputContext(Game *game);

    virtual void up() =0;
    virtual void down() =0;
    virtual void left() =0;
    virtual void right() =0;

    virtual void action() =0;
    virtual void alternate() =0;

    virtual void back() =0;

    virtual void mouse_position(double x, double y) { (void) x; (void) y; }
    // virtual void left_click() =0;
    // virtual void right_click() =0;

    Game *get_game() const;

    void set_repeat_delay(int v);
    int get_repeat_delay() const;
    void set_repeat_rate(int v);
    int get_repeat_rate() const;
private:

    int repeat_delay, repeat_rate;
    Game *_game;
};