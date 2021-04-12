#include "menuitem.hpp"

MenuItem::MenuItem(Menu *parent)
:   InputContext(parent->get_game())
,   PhysicsObject(parent, {0, 0}, true, 1.0)
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