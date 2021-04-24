#include "manager.hpp"

ResourceManager &ResourceManager::ref()
{
    static ResourceManager rm;
    return rm;
}