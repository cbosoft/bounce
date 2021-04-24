#pragma once

#include <armadillo>

class InputContext {
public:
    InputContext();

    virtual void up() =0;
    virtual void down() =0;
    virtual void left() =0;
    virtual void right() =0;

    virtual void action() =0;
    virtual void alternate() =0;

    virtual void back() =0;

    virtual void cursor_position(const arma::vec2 &pos) { (void) pos; }
    virtual void zoom(const arma::vec2 &pos) { (void) pos; }

    void set_repeat_delay(int v);
    int get_repeat_delay() const;
    void set_repeat_rate(int v);
    int get_repeat_rate() const;
private:

    int repeat_delay, repeat_rate;
};