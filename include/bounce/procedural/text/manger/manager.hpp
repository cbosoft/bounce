#pragma once

#include <string>
#include <map>

#include "../collection/collection.hpp"

class TextManager {
public:
    static TextManager &ref();
    TextManager(const TextManager &other) =delete;
    TextManager &operator=(const TextManager &other) =delete;
    ~TextManager();

    const std::string &get_string(const std::string &collection_name, const std::string &id);

private:
    TextManager();

    std::map<std::string, TextCollection *> _collections;
};