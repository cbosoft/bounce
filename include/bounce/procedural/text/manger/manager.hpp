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

    TextCollection *get_collection(const std::string &collection_name);

private:
    TextManager();

    std::map<std::string, TextCollection *> _collections;
};