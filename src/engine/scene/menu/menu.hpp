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

    void up_pressed() override;
    void left_pressed() override;
    void down_pressed() override;
    void right_pressed() override;

    void action_pressed() override;
    void alternate_pressed() override;
    void back_pressed() override;

    void connect_vertical();
    void connect_horizontal();

private:
    std::vector<MenuItem *> items;
    MenuItem *selected;
};