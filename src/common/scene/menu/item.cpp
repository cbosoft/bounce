#include "menu.hpp"
#include "menuitem/menuitem.hpp"

void Menu::set_selected(MenuItem *item)
{
    if (this->selected)
        this->style_unselected(this->selected);
    this->selected = item;
    this->style_selected(this->selected);
}

void Menu::style_selected(MenuItem *item)
{
    static const double dr = 0.5;
    double r = item->get_radius();
    item->set_radius(r + dr);
}

void Menu::style_unselected(MenuItem *item)
{
    static const double dr = 0.5;
    double r = item->get_radius();
    item->set_radius(r - dr);
}

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

void Menu::alternate() { if (this->selected) this->selected->alternate(); }
void Menu::back() { if (this->selected) this->selected->back(); }
