#include <bounce/game/game.hpp>
#include <bounce/input/manager.hpp>

/**
 * Process the input queue in order.
 */
void InputManager::handle_input() {
    for (const auto &input : this->_state_queue) {
        this->run_input_state(input);
    }
    this->_state_queue.clear();
}

/**
 * For the given input state, run action methods of the current context depending on the button press information.
 * @param input_state The state to process.
 */
void InputManager::run_input_state(const InputState &input_state)
{
    InputContext *context = Game::ref().get_context();
    if (context) {
        switch (input_state.up) {
            case BTN_NULL:                             break;
            case BTN_PRESSED:  context->up_pressed();  break;
            case BTN_REPEATED: context->up_repeated(); break;
            case BTN_RELEASED: context->up_released(); break;
        }
        switch (input_state.left) {
            case BTN_NULL:                               break;
            case BTN_PRESSED:  context->left_pressed();  break;
            case BTN_REPEATED: context->left_repeated(); break;
            case BTN_RELEASED: context->left_released(); break;
        }
        switch (input_state.down) {
            case BTN_NULL:                               break;
            case BTN_PRESSED:  context->down_pressed();  break;
            case BTN_REPEATED: context->down_repeated(); break;
            case BTN_RELEASED: context->down_released(); break;
        }
        switch (input_state.right) {
            case BTN_NULL:                                break;
            case BTN_PRESSED:  context->right_pressed();  break;
            case BTN_REPEATED: context->right_repeated(); break;
            case BTN_RELEASED: context->right_released(); break;
        }
        switch (input_state.action) {
            case BTN_NULL:                                 break;
            case BTN_PRESSED:  context->action_pressed();  break;
            case BTN_REPEATED: context->action_repeated(); break;
            case BTN_RELEASED: context->action_released(); break;
        }
        switch (input_state.alternative) {
            case BTN_NULL:                               break;
            case BTN_PRESSED:  context->alternate_pressed();  break;
            case BTN_REPEATED: context->alternate_repeated(); break;
            case BTN_RELEASED: context->alternate_released(); break;
        }
        switch (input_state.back) {
            case BTN_NULL:                               break;
            case BTN_PRESSED:  context->back_pressed();  break;
            case BTN_REPEATED: context->back_repeated(); break;
            case BTN_RELEASED: context->back_released(); break;
        }
        switch (input_state.char_state) {
            case BTN_NULL:                               break;
            case BTN_PRESSED:  context->key_char_pressed(input_state.ch);  break;
            case BTN_REPEATED: context->key_char_repeated(input_state.ch); break;
            case BTN_RELEASED: context->key_char_released(input_state.ch); break;
        }

        if (input_state.cursor_moved) context->cursor_position(input_state.cursor);
        if (input_state.zoomed) context->zoom(input_state.zoom);
    }
}