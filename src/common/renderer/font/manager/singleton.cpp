#include "manager.hpp"

FontManager& FontManager::ref()
{
    static FontManager tm;
    return tm;
}
