#include <filesystem>

#include <bounce/renderer/renderer.hpp>
#include <bounce/logging/logger.hpp>

/**
 * Load texture into Renderer from resource dir.
 *
 * \p name is passed to the Texture constructor, where it is resolved to a path using the ResourcesManager.
 *
 * \sa Texture
 * \sa ResourceManager::get_path
 *
 * @param name Name of the texture in the resources directory.
 */
void Renderer::add_texture(const std::string &name)
{
    this->textures[name] = new Texture(name);
}

/**
 * Give a texture to the Renderer, with \p name. The Texture pointer is then owned by the Renderer.
 *
 * @param name Name of the texture, this is used when setting the texture on a renderable.
 * @param texture Pointer to the Texture.
 */
void Renderer::add_texture(const std::string &name, Texture *texture)
{
    this->textures[name] = texture;
}

/**
 * Get a cached texture from the Renderer.
 *
 * Texture(s) are stored internally in a dictionary cache, keyed by a \p name. If a Texture is not found in the cache,
 * then it is attempted to be read from disk (Renderer::add_texture). If that fails, a warning is logged and an empty
 * texture is returned ("null").
 *
 * @param name Name of the texture.
 * @return Pointer to the Texture.
 */
Texture *Renderer::get_texture(const std::string &name)
{
    auto it = this->textures.find(name);
    if (it == this->textures.end()) {
        // if the texture name is a resource path, try to load it
        try {
            // raises runtime error if name is not found
            this->textures[name] = new Texture(name);
        }
        catch (const std::runtime_error &e) {
            Logger::ref() << LL_WARN << "Could not find texture \"" << name <<"\" and could not load it from file.\n";
            Logger::ref() << LL_WARN << "Returning null texture.\n";
            return this->textures["null"];
        }
    }
    return this->textures[name];
}