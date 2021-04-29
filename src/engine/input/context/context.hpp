#pragma once

#include <armadillo>

/**
 * Class to which input is sent.
 *
 * An InputContext is acted upon by the InputManager during InputManahger#handle_input by calling its
 * <em>action methods</em>:
 *  - InputContext#up_pressed
 *  - InputContext#up_repeated
 *  - InputContext#up_released
 *  - InputContext#left_pressed
 *  - InputContext#left_repeated
 *  - InputContext#left_released
 *  - InputContext#down_pressed
 *  - InputContext#down_repeated
 *  - InputContext#down_released
 *  - InputContext#right_pressed
 *  - InputContext#right_repeated
 *  - InputContext#right_released
 *  - InputContext#action_pressed
 *  - InputContext#action_repeated
 *  - InputContext#action_released
 *  - InputContext#alternate_pressed
 *  - InputContext#alternate_repeated
 *  - InputContext#alternate_released
 *  - InputContext#back_pressed
 *  - InputContext#back_repeated
 *  - InputContext#back_released
 *
 * In addition to the button press actions above, there are calls to cursor position (InputContext#cursor_position) and
 * zoom level methods (InputContext#zoom), which can represent mouse and scroll wheel positions for keyboard input, or
 * right joystick positions for gamepads.
 */
class InputContext {
public:
    /** Action method called on 'up' button press.
     * The default implementation does nothing. */
    virtual void up_pressed() {};
    virtual void up_repeated() {};
    virtual void up_released() {};

    /** Action method called on 'down' button press.
     * The default implementation does nothing. */
    virtual void down_pressed() {};
    virtual void down_repeated() {};
    virtual void down_released() {};

    /** Action method called on 'left' button press.
     * The default implementation does nothing. */
    virtual void left_pressed() {};
    virtual void left_repeated() {};
    virtual void left_released() {};

    /** Action method called on 'right' button press.
     * The default implementation does nothing. */
    virtual void right_pressed() {};
    virtual void right_repeated() {};
    virtual void right_released() {};

    /** Action method called on 'action' button press.
     * The default implementation does nothing. */
    virtual void action_pressed() {};
    virtual void action_repeated() {};
    virtual void action_released() {};

    /** Action method called on 'alternate action' button press.
     * The default implementation does nothing. */
    virtual void alternate_pressed() {};
    virtual void alternate_repeated() {};
    virtual void alternate_released() {};

    /** Action method called on 'back' button press.
     * The default implementation does nothing. */
    virtual void back_pressed() {};
    virtual void back_repeated() {};
    virtual void back_released() {};

    /** Action method called when cursor changes position (mouse, left joystick -> aiming things).
     * The default implementation does nothing. */
    virtual void cursor_position(const arma::vec2 &pos) { (void) pos; }

    /** Action method called when zoom level changes.
     * The default implementation does nothing. */
    virtual void zoom(const arma::vec2 &pos) { (void) pos; }
};