#include "menuitem.hpp"

void MenuItem::up() { if (this->item_above) this->parent->set_selected(this->item_above); }
void MenuItem::left() { if (this->item_left) this->parent->set_selected(this->item_left); }
void MenuItem::down() { if (this->item_below) this->parent->set_selected(this->item_below); }
void MenuItem::right() { if (this->item_right) this->parent->set_selected(this->item_right); }

void MenuItem::connect_up(MenuItem *o) { this->item_above = o; o->item_below = this; }
void MenuItem::connect_left(MenuItem *o) { this->item_left = o; o->item_right = this; }
void MenuItem::connect_down(MenuItem *o) { this->item_below = o; o->item_above = this; }
void MenuItem::connect_right(MenuItem *o) { this->item_right = o; o->item_left = this; }
