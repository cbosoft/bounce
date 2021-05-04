#include <bounce/procedural/text/manger/manager.hpp>

TextManager::~TextManager()
{
    for (auto kv : this->_collections)
        delete kv.second;
}
