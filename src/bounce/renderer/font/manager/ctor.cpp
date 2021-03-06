#include <bounce/renderer/font/manager/manager.hpp>

FontManager::FontManager()
: _ft_lib(nullptr)
{
    if (FT_Init_FreeType(&this->_ft_lib))
        throw std::runtime_error("Could not initialise freetype.");
}
