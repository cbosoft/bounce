#include <bounce/resources/manager.hpp>

ResourceManager &ResourceManager::ref()
{
    static ResourceManager rm;
    return rm;
}