#include "menu.hpp"

Menu::Menu(const std::string &name)
:   Scene(name)
,   selected(nullptr)
{
    this->set_repeat_delay(300);
}