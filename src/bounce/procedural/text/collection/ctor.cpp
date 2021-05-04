#include <bounce/procedural/text/collection/collection.hpp>
#include <bounce/resources/manager.hpp>

TextCollection::TextCollection(const std::string &name)
{
    ResourceManager &rm = ResourceManager::ref();
    json j = rm.get_metadata("text", name);

    for (const auto &[key, strings] : j.items()) {
        for (const json &str : strings) {
            this->_strings[key].push_back(str);
        }
    }
}