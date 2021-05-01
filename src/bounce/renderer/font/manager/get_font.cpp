#include <sstream>

#include <bounce/logging/logger.hpp>
#include <bounce/resources/manager.hpp>
#include <bounce/renderer/font/manager/manager.hpp>

Font *FontManager::create_front(const std::string &name, int size)
{
    std::string path = ResourceManager::ref().get_path("fonts", name, ".ttf");
    FT_Face face;
    if (FT_New_Face(this->_ft_lib, path.c_str(), 0, &face)) {
        Logger::ref() << LL_WARN << "Could not load font \"" << path << "\"\n";
        return nullptr;
    }

    return new Font(face, size);
}

Font *FontManager::get_font(const std::string &name, int font_size)
{
    std::stringstream ss;
    ss << name << "@" << font_size;
    std::string key = ss.str();

    auto it = this->font_cache.find(key);
    if (it != font_cache.end()) {
        return it->second;
    }

    Font *font = this->create_front(name, font_size);
    if (font) {
        this->font_cache[key] = font;
    }
    else if (!this->font_cache.empty()) {
        auto kv = this->font_cache.begin();
        Logger::ref() << LL_WARN << "Falling back on \"" << kv->first << "\".";
        font = kv->second;
    }
    else {
        Logger::ref() << "Could not load requested font \"" << name << "\" and no fallback found.\n";
    }

    return font;
}