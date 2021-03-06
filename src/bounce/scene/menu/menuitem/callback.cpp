#include <bounce/scene/menu/menuitem/menuitem.hpp>

void MenuItem::set_callback_up(menu_callback cb) { this->_cb_up = cb; }
void MenuItem::set_callback_left(menu_callback cb) { this->_cb_left = cb; }
void MenuItem::set_callback_down(menu_callback cb) { this->_cb_down = cb; }
void MenuItem::set_callback_right(menu_callback cb) { this->_cb_right = cb; }
void MenuItem::set_callback_action(menu_callback cb) {
    this->_cb_action = cb; }
void MenuItem::set_callback_alternate(menu_callback cb) { this->_cb_alt = cb; }
void MenuItem::set_callback_back(menu_callback cb) { this->_cb_back = cb; }

void MenuItem::up_pressed() {
    if (this->_cb_up)this->_cb_up(this); }
void MenuItem::left_pressed() { if (this->_cb_left)this->_cb_left(this); }
void MenuItem::down_pressed() { if (this->_cb_down)this->_cb_down(this); }
void MenuItem::right_pressed() { if (this->_cb_right)this->_cb_right(this); }
void MenuItem::action_pressed() {
    if (this->_cb_action)this->_cb_action(this); }
void MenuItem::alternate_pressed() { if (this->_cb_alt)this->_cb_alt(this); }
void MenuItem::back_pressed() { if (this->_cb_back)this->_cb_back(this); }
