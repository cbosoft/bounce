#include <bounce/scene/menu/text_input_popup/text_input_popup.hpp>
#include <bounce/game/game.hpp>
#include <bounce/events.hpp>

void TextInputPopUp::action_pressed()
{
    std::cerr << "action" << std::endl;
    Game::ref().add_event(new PopSceneTransitionEvent());
}

void TextInputPopUp::back_pressed()
{
    std::cerr << "back" << std::endl;
    Game::ref().add_event(new PopSceneTransitionEvent());
}

void TextInputPopUp::key_char_pressed(char ch)
{
    this->_input << ch;
    std::string t = this->_input.str();
    this->_txt->set_text(t);
}