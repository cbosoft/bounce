#include "menuitem.hpp"

MenuItem::MenuItem(Menu *parent)
:   InputContext(parent->get_game())
,   Transform(parent)
,   item_above(nullptr)
,   item_left(nullptr)
,   item_below(nullptr)
,   item_right(nullptr)
,   parent(parent)
{

}