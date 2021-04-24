#include "manager.hpp"
#include <iostream>

bool InputManager::check_input_rate(unsigned int key)
{
    InputContext *context = this->get_context();
    if (!context) {
        return false;
    }

    auto now = std::chrono::system_clock::now();

    auto *bool_prev = (const bool *)&this->previous_state;
    if (!bool_prev[key]) {
        this->previous_press[key] = now;
        return true;
    }

    auto it = this->previous_press.find(key);
    if (it == this->previous_press.end()) {
        this->previous_press[key] = now;
        return true;
    }
    auto time_last_pressed = it->second;
    auto dt = now - time_last_pressed;

    auto len_millis = int(std::chrono::duration_cast<std::chrono::milliseconds>(dt).count());
    if (len_millis > context->get_repeat_delay()) {
        this->previous_press[key] = now;
        return true;
    }

    return false;
}