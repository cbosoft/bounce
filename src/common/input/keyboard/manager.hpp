#pragma once

#include "../manager.hpp"

class KeyboardInputManager : public InputManager {
public:
    InputState read_input_state() override;
};