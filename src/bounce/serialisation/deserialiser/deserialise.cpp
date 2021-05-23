#include <list>

#include <bounce/serialisation/deserialiser/deserialiser.hpp>
#include <bounce/scene/scene.hpp>
#include <bounce/physics/collider/collider.hpp>
#include <bounce/physics/rigidbody/rigidbody.hpp>
#include <bounce/logging/logger.hpp>
#include <bounce/renderer/renderables.hpp>

Transform *Deserialiser::deserialise(json j)
{
    std::string type_s = j["type"];
    if (type_s.empty()) {
        throw std::runtime_error("error loading from json; type not specified.");
    }

    Transform *rv = nullptr;
    if (type_s == "transform") {
        rv = new Transform(j);
    }
    else if (type_s == "collider") {
        rv = new Collider(j);
    }
    else if (type_s == "rigidbody") {
        rv = new Rigidbody(j);
    }
    else if (type_s == "scene") {
        rv = new Scene(j, 0);
    }
    else if (type_s == "mesh renderable") {
        rv = new MeshRenderable(j);
    }
    else if (type_s == "camera") {
        rv = new Camera(j);
    }
    else if (type_s == "rectangle transform") {
        rv = new RectTransform(j);
    }
    else if (type_s == "menu") {
        // TODO
    }
    else if (type_s == "menuitem") {
        // TODO
    }

    if (rv == nullptr) {
        throw std::runtime_error("error loading from json; type not understood.");
    }
    return rv;
}