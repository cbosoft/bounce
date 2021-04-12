#pragma once

#include "../../../physics/object/object.hpp"
#include "../menu.hpp"

class MenuItem : public InputContext, public PhysicsObject {
public:
    explicit MenuItem(Menu *parent);

    void up() override;
    void left() override;
    void down() override;
    void right() override;

    void back() override {}
    void alternate() override {}

    void connect_up(MenuItem *o);
    void connect_left(MenuItem *o);
    void connect_down(MenuItem *o);
    void connect_right(MenuItem *o);

    Menu *get_parent_menu();

private:
    MenuItem *item_above, *item_left, *item_below, *item_right;
    Menu *parent;
};