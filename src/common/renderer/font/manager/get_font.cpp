#include <iostream>
#include <sstream>

#include "manager.hpp"

Font *FontManager::create_front(const std::string &path, int size)
{
    FT_Face face;
    if (FT_New_Face(this->_ft_lib, path.c_str(), 0, &face)) {
        std::cerr << "Could not load font \"" << path << "\"" << std::endl;
        return nullptr;
    }

    return new Font(face, size);
}

Font *FontManager::get_font(const std::string &font_name, int font_size)
{
    std::stringstream ss;
    ss << font_name << "@" << font_size;
    std::string key = ss.str();

    auto it = this->font_cache.find(key);
    if (it != font_cache.end()) {
        return it->second;
    }

    Font *font = this->create_front(font_name, font_size);
    if (font) {
        this->font_cache[key] = font;
    }
    else if (!this->font_cache.empty()) {
        auto kv = this->font_cache.begin();
        std::cerr << "Falling back on \"" << kv->first << "\"" << std::endl;
        font = kv->second;
    }
    else {
        std::cerr << "Could not load font and no fallback found." << std::endl;
    }

    return font;
}