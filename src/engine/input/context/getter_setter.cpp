#include "context.hpp"

/**
 * Set \p repeat_delay value - time between a first press and begining a repeat sequence.
 *
 * @param v The number of milliseconds to set the repeat delay to.
 */
void InputContext::set_repeat_delay(int v)
{
    this->repeat_delay = v;
}

/**
 * @return The current \p repeat_delay.
 */
int InputContext::get_repeat_delay() const
{
    return this->repeat_delay;
}

/**
 * Set \p repeat_rate value - the time between button activations while repeating. Not a rate, actually inverse rate or
 * period of repetition.
 *
 * @param v The number of milliseconds to set the repeat rate to.
 */
void InputContext::set_repeat_rate(int v)
{
    this->repeat_rate = v;
}

/**
 * @return The current \p repeat_rate.
 */
int InputContext::get_repeat_rate() const
{
    return this->repeat_rate;
}
