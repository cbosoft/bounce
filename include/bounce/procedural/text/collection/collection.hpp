#pragma once

#include <vector>
#include <map>
#include <string>

class TextCollection {
public:
    TextCollection(const std::string &name);

    const std::string &get_string(const std::string &id);

private:
    std::map<std::string, std::vector<std::string>> _strings;
};
