#pragma once

#include <sstream>

#include "../menu.hpp"

class TextInputPopUp : public Menu {
public:
    TextInputPopUp(const std::string &prompt, const std::string &font_name);

    void action_pressed() override;
    void back_pressed() override;
    void key_char_pressed(char ch) override;

private:
    TextRenderable *_txt;
    std::string _prompt;
    std::stringstream _input;
};