#include "menuitem.hpp"

void MenuItem::select_up(MenuItem *i) { if (i->item_above) i->parent->set_selected(i->item_above); }
void MenuItem::select_left(MenuItem *i) { if (i->item_left) i->parent->set_selected(i->item_left); }
void MenuItem::select_down(MenuItem *i) { if (i->item_below) i->parent->set_selected(i->item_below); }
void MenuItem::select_right(MenuItem *i) { if (i->item_right) i->parent->set_selected(i->item_right); }

void MenuItem::connect_up(MenuItem *o)
{
    this->item_above = o;
    this->set_callback_up(MenuItem::select_up);
    o->item_below = this;
    o->set_callback_down(MenuItem::select_down);
}

void MenuItem::connect_left(MenuItem *o)
{
    this->item_left = o;
    this->set_callback_left(MenuItem::select_left);
    o->item_right = this;
    this->set_callback_right(MenuItem::select_right);
}

void MenuItem::connect_down(MenuItem *o)
{
    this->item_below = o;
    this->set_callback_down(MenuItem::select_down);
    o->item_above = this;
    this->set_callback_up(MenuItem::select_up);
}

void MenuItem::connect_right(MenuItem *o)
{
    this->item_right = o;
    this->set_callback_right(MenuItem::select_right);
    o->item_left = this;
    this->set_callback_left(MenuItem::select_left);
}
