#include <list>

#include <bounce/serialisation/deserialiser/deserialiser.hpp>

Transform *Deserialiser::deserialise(json j)
{
    std::string type_s = j["type"];
    if (type_s.empty()) {
        throw std::runtime_error("error loading from json; type not specified.");
    }

    const static std::size_t transform_hash = std::hash<std::string>{}("transform");
    const static std::size_t object_hash = std::hash<std::string>{}("object");
    const static std::size_t scene_hash = std::hash<std::string>{}("scene");
    const static std::size_t menu_hash = std::hash<std::string>{}("menu");
    const static std::size_t menuitem_hash = std::hash<std::string>{}("menuitem");

    std::size_t type_hash = std::hash<std::string>{}(type_s);
    Transform *rv = nullptr;
    if (type_hash == transform_hash) {
        rv = new Transform(j);
    }
    else if (type_hash == object_hash) {
        // TODO
    }
    else if (type_hash == scene_hash) {
        // TODO
    }
    else if (type_hash == menu_hash) {
        // TODO
    }
    else if (type_hash == menuitem_hash) {
        // TODO
    }

    if (rv == nullptr) {
        throw std::runtime_error("error loading from json; type not understood.");
    }
    return rv;
}