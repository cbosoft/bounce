#include "menu.hpp"
#include "menuitem/menuitem.hpp"

void Menu::set_selected(MenuItem *item)
{
    this->selected = item;



void Menu::add_item(MenuItem *item)
{
    this->items.push_back(item);
    this->add_object(item);
}

void Menu::up() { if (this->selected) this->selected->up(); }
void Menu::left() { if (this->selected) this->selected->left(); }
void Menu::down() { if (this->selected) this->selected->down(); }
void Menu::right() { if (this->selected) this->selected->right(); }

void Menu::action() { if (this->selected) this->selected->action(); }

void Menu::alternate() {}
void Menu::back() {}
