#pragma once

#include <armadillo>

/**
 * Class to which input is sent.
 *
 * When a InputManager::handle_input is called, the input is sent to an instance of InputContext, by calling its
 * <em>action methods</em>:
 *  - InputContext#up
 *  - InputContext#left
 *  - InputContext#down
 *  - InputContext#right
 *  - InputContext#action
 *  - InputContext#alternate
 *  - InputContext#back
 *
 * In addition to the button press actions above, there are calls to cursor position (InputContext#cursor_position) and
 * zoom level methods (InputContext#zoom), which can represent mouse and scroll wheel positions for keyboard input, or
 * right joystick positions for gamepads.
 *
 * In addition, stores information about how \m frequently an input should be processed - the input \p repeat_rate and
 * input \p repeat_delay. The former, annoyingly, is a misnomer and is not a rate but inverse rate or period. Rate just
 * sounded nicer.
 */
class InputContext {
public:
    InputContext();

    /** Action method called on 'up' button press.
     * The default implementation does nothing. */
    virtual void up() {};

    /** Action method called on 'down' button press.
     * The default implementation does nothing. */
    virtual void down() {};

    /** Action method called on 'left' button press.
     * The default implementation does nothing. */
    virtual void left() {};

    /** Action method called on 'right' button press.
     * The default implementation does nothing. */
    virtual void right() {};

    /** Action method called on 'action' button press.
     * The default implementation does nothing. */
    virtual void action() {};

    /** Action method called on 'alternate action' button press.
     * The default implementation does nothing. */
    virtual void alternate() {};

    /** Action method called on 'back' button press.
     * The default implementation does nothing. */
    virtual void back() {};

    /** Action method called when cursor changes position (mouse, left joystick -> aiming things).
     * The default implementation does nothing. */
    virtual void cursor_position(const arma::vec2 &pos) { (void) pos; }

    /** Action method called when zoom level changes.
     * The default implementation does nothing. */
    virtual void zoom(const arma::vec2 &pos) { (void) pos; }

    void set_repeat_delay(int v);
    [[nodiscard]] int get_repeat_delay() const;
    void set_repeat_rate(int v);
    [[nodiscard]] int get_repeat_rate() const;

private:
    int repeat_delay, repeat_rate;
};