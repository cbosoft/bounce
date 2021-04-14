#include "menuitem.hpp"

MenuItem::MenuItem(Menu *parent)
:   InputContext(parent->get_game())
,   Object(parent, {0, 0}, true, 1.0)
,   _cb_up(nullptr)
,   _cb_left(nullptr)
,   _cb_down(nullptr)
,   _cb_right(nullptr)
,   _cb_action(nullptr)
,   _cb_alt(nullptr)
,   _cb_back(nullptr)
,   item_above(nullptr)
,   item_left(nullptr)
,   item_below(nullptr)
,   item_right(nullptr)
,   parent(parent)
{

}

Menu *MenuItem::get_parent_menu()
{
    return this->parent;
}