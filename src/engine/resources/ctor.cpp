#include "manager.hpp"
#include "../logging/logger.hpp"

ResourceManager::ResourceManager()
{
    this->set_root();
    Logger::ref() << LL_INFO << "Resources dir found at " << this->_root << "\n";
}