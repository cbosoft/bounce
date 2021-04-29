#pragma once

#include "../../../object/object.hpp"
#include "../menu.hpp"

class MenuItem;
typedef void (*menu_callback)(MenuItem *item);

class MenuItem : public InputContext, public Transform {
public:
    explicit MenuItem(Menu *parent);

    void up_pressed() override;
    void left_pressed() override;
    void down_pressed() override;
    void right_pressed() override;

    void action_pressed() override;
    void alternate_pressed() override;
    void back_pressed() override;

    void set_callback_up(menu_callback cb);
    void set_callback_left(menu_callback cb);
    void set_callback_down(menu_callback cb);
    void set_callback_right(menu_callback cb);
    void set_callback_action(menu_callback cb);
    void set_callback_alternate(menu_callback cb);
    void set_callback_back(menu_callback cb);

    void connect_up(MenuItem *o);
    void connect_left(MenuItem *o);
    void connect_down(MenuItem *o);
    void connect_right(MenuItem *o);

    static void select_left(MenuItem *i);
    static void select_up(MenuItem *i);
    static void select_down(MenuItem *i);
    static void select_right(MenuItem *i);

    Menu *get_parent_menu();

    virtual void highlight();
    virtual void unhighlight();

private:

    menu_callback _cb_up, _cb_left, _cb_down, _cb_right, _cb_action, _cb_alt, _cb_back;
    MenuItem *item_above, *item_left, *item_below, *item_right;
    Menu *parent;
};