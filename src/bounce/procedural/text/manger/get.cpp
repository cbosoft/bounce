#include <bounce/procedural/text/manger/manager.hpp>
#include <bounce/resources/manager.hpp>

const std::string & TextManager::get_string(const std::string &collection_name, const std::string &id)
{
    // check if collection already loaded; load if not
    auto it = this->_collections.find(collection_name);
    if (it == this->_collections.end()) {
        this->_collections[collection_name] = new TextCollection(collection_name);
    }

    TextCollection *collection = this->_collections[collection_name];
    return collection->get_string(id);
}