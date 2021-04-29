#include "manager.hpp"
#include "../game/game.hpp"

/**
 * Limit the rate of a button press. Used especially in menus to facilitate navigation.
 *
 * Checks how long it has been since the button (with index \p key) was last pressed - if it is too short, then refuse
 * to activate the key.
 *
 * @param key The index of button in the InputState.
 * @return Boolean indicating whether the button should be allowed to be activated, or ignored.
 */
bool InputManager::check_input_rate(unsigned int key)
{
    InputContext *context = Game::ref().get_context();
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