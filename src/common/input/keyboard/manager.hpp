#pragma once

#include "../manager.hpp"

class KeyboardInputManager : public InputManager {
public:
    void handle_input() override;
};