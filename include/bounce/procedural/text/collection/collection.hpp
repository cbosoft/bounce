#pragma once

#include <list>
#include <map>
#include <string>

class TextCollection {
public:
    explicit TextCollection(const std::string &name);

    const std::string &get_string(const std::string &id);
    std::string get_string_and_consume(const std::string &id);

private:
    std::map<std::string, std::list<std::string>> _strings;
};
