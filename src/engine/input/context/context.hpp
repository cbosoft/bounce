#pragma once

#include <armadillo>

class InputContext {
public:
    InputContext();

    virtual void up() {};
    virtual void down() {};
    virtual void left() {};
    virtual void right() {};

    virtual void action() {};
    virtual void alternate() {};

    virtual void back() {};

    virtual void cursor_position(const arma::vec2 &pos) { (void) pos; }
    virtual void zoom(const arma::vec2 &pos) { (void) pos; }

    void set_repeat_delay(int v);
    int get_repeat_delay() const;
    void set_repeat_rate(int v);
    int get_repeat_rate() const;
private:

    int repeat_delay, repeat_rate;
};