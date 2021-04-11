#pragma once
#include <list>
#include "../scene.hpp"

class MenuItem;
class Menu : public Scene {
public:
    Menu(Game *game, const std::string &name);

    void set_selected(MenuItem *item);

    void up() override;
    void left() override;
    void down() override;
    void right() override;

    void action() override;
    void alternate() override;
    void back() override;

private:
    std::list<MenuItem *> items;
    MenuItem *selected;
};