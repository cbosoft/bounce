#pragma once
#include <list>
#include "../scene.hpp"

class MenuItem;
class Menu : public Scene {
public:
    Menu(const std::string &name);

    void set_selected(MenuItem *item);
    void add_item(MenuItem *item);
    const std::vector<MenuItem *> &get_items() const;

    void up() override;
    void left() override;
    void down() override;
    void right() override;

    void action() override;
    void alternate() override;
    void back() override;

    void connect_vertical();
    void connect_horizontal();

private:
    std::vector<MenuItem *> items;
    MenuItem *selected;
};