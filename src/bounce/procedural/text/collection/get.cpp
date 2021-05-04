#include <bounce/procedural/text/collection/collection.hpp>
#include <bounce/procedural/util/select_randomly.hpp>

const std::string & TextCollection::get_string(const std::string &id)
{
    const static std::string whoopsie = "WOOPS!";
    auto it = this->_strings.find(id);
    if (it == this->_strings.end()) {
        return whoopsie;
    }

    const auto &vec = it->second;
    if (vec.empty())
        return whoopsie;

    return *select_randomly(vec.begin(), vec.end());
}
