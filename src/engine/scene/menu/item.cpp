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

void Menu::up_pressed() { if (this->selected) this->selected->up_pressed(); }
void Menu::left_pressed() { if (this->selected) this->selected->left_pressed(); }
void Menu::down_pressed() { if (this->selected) this->selected->down_pressed(); }
void Menu::right_pressed() { if (this->selected) this->selected->right_pressed(); }

void Menu::action_pressed() { if (this->selected) this->selected->action_pressed(); }

void Menu::alternate_pressed() { if (this->selected) this->selected->alternate_pressed(); }
void Menu::back_pressed() { if (this->selected) this->selected->back_pressed(); }

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

const std::vector<MenuItem *> &Menu::get_items() const
{
    return this->items;
}