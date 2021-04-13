#include "manager.hpp"

void InputManager::handle_input()
{
    InputState current_state = this->read_input_state(), current_copy = current_state;
    auto *bool_state = (bool *)&current_state;
    for (unsigned int i = 0; i < 7; i++) {
        if (bool_state[i]) {
            // sets state to false if too soon for a second input
            bool_state[i] = this->check_input_rate(i);
        }
    }

    InputContext *context = this->get_context();
    if (context) {
        if (current_state.up) context->up();
        if (current_state.left) context->left();
        if (current_state.down) context->down();
        if (current_state.right) context->right();
        if (current_state.action) context->action();
        if (current_state.alternative) context->alternate();
        if (current_state.back) context->back();
    }

    this->previous_state = current_copy;
}