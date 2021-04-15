#include "manager.hpp"
#include <iostream>

ResourceManager::ResourceManager()
{
    this->set_root();
    std::cerr << "Resources dir found at " << this->_root << std::endl;
}