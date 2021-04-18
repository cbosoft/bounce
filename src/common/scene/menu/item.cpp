#include "menu.hpp"
#include "menuitem/menuitem.hpp"

void Menu::set_selected(MenuItem *item)
{
    if (this->selected)
        this->selected->unhighlight();
    this->selected = item;
    if (this->selected)
        this->selected->highlight();
}

void Menu::add_item(MenuItem *item)
{
    this->items.push_back(item);
    item->unhighlight();
    if (!this->selected)
        this->set_selected(item);
}

void Menu::up() { if (this->selected) this->selected->up(); }
void Menu::left() { if (this->selected) this->selected->left(); }
void Menu::down() { if (this->selected) this->selected->down(); }
void Menu::right() { if (this->selected) this->selected->right(); }

void Menu::action() { if (this->selected) this->selected->action(); }

void Menu::alternate() { if (this->selected) this->selected->alternate(); }
void Menu::back() { if (this->selected) this->selected->back(); }

void Menu::connect_vertical()
{
    int sz = int(this->items.size());
    for (int i = 0; i < sz; i++) {
        int j = (i + 1) % sz;
        auto *next = this->items[j];
        auto *prev = this->items[i];
        prev->connect_down(next);
    }
}

void Menu::connect_horizontal()
{
    int sz = int(this->items.size());
    for (int i = 0; i < sz; i++) {
        int j = (i + 1) % sz;
        auto *next = this->items[j];
        auto *prev = this->items[i];
        prev->connect_left(next);
    }
}
