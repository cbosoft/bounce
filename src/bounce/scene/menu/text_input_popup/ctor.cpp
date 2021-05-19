#include <bounce/scene/menu/text_input_popup/text_input_popup.hpp>

TextInputPopUp::TextInputPopUp(const std::string &prompt, const std::string &font)
:   Menu("text input "+prompt)
,   _prompt(prompt)
{
    auto *bg = new RectangleMeshRenderable(100, 25);
    bg->set_parent(this);
    bg->set_colour(Colours::black);
    bg->set_border_size(1.0);
    this->_txt = new TextRenderable("", font, 80);
    this->_txt->set_parent(this);
    this->_insubstantial = true;
}