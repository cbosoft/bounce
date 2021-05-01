#include <bounce/renderer/font/manager/manager.hpp>

FontManager& FontManager::ref()
{
    static FontManager tm;
    return tm;
}
