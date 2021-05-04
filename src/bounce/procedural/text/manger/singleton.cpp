#include <bounce/procedural/text/manger/manager.hpp>

TextManager & TextManager::ref()
{
    static TextManager tm;
    return tm;
}