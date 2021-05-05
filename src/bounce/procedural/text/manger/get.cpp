#include <bounce/procedural/text/manger/manager.hpp>
#include <bounce/resources/manager.hpp>

TextCollection *TextManager::get_collection(const std::string &collection_name)
{
    // check if collection already loaded; load if not
    auto it = this->_collections.find(collection_name);
    if (it == this->_collections.end()) {
        this->_collections[collection_name] = new TextCollection(collection_name);
    }
    // TODO what if the collection doesn't exist?

    return this->_collections[collection_name];
}