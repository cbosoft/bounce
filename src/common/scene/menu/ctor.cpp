#include "menu.hpp"

Menu::Menu(Game *game, const std::string &name)
:   Scene(game, name)
,   selected(nullptr)
{
    this->set_repeat_delay(300);
}