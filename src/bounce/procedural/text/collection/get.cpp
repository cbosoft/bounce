#include <bounce/procedural/text/collection/collection.hpp>
#include <bounce/procedural/util/select_randomly.hpp>

const std::string & TextCollection::get_string(const std::string &id)
{
    const static std::string whoopsie = "WOOPS!";
    auto it = this->_strings.find(id);
    if (it == this->_strings.end()) {
        return whoopsie; // TODO exception?
    }

    const auto &lst = it->second;
    if (lst.empty())
        return whoopsie; // TODO exception?

    return *select_randomly(lst.begin(), lst.end());
}

std::string TextCollection::get_string_and_consume(const std::string &id)
{
    const static std::string whoopsie = "WOOPS!";
    auto it = this->_strings.find(id);
    if (it == this->_strings.end()) {
        return whoopsie; // TODO exception?
    }

    auto &lst = it->second;
    if (lst.empty())
        return whoopsie; // TODO exception?

    auto selection = select_randomly(lst.begin(), lst.end());
    std::string rv = *selection;
    lst.erase(selection);
    return rv;
}