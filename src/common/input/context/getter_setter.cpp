#include "context.hpp"

void InputContext::set_repeat_delay(int v)
{
    this->repeat_delay = v;
}

int InputContext::get_repeat_delay() const
{
    return this->repeat_delay;
}

void InputContext::set_repeat_rate(int v)
{
    this->repeat_rate = v;
}

int InputContext::get_repeat_rate() const
{
    return this->repeat_rate;
}
