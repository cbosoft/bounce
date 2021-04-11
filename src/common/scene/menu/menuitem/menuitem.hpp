#pragma once

#include "../menu.hpp"

class MenuItem : public InputContext, public Transform {
public:
    explicit MenuItem(Menu *parent);

    void up() override;
    void left() override;
    void down() override;
    void right() override;

    void connect_up(MenuItem *o);
    void connect_left(MenuItem *o);
    void connect_down(MenuItem *o);
    void connect_right(MenuItem *o);

private:
    MenuItem *item_above, *item_left, *item_below, *item_right;
    Menu *parent;
};