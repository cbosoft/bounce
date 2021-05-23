#pragma once

#include <map>
#include <string>

#include "camera/camera.hpp"
#include "../input/context/context.hpp"
#include "../transform/transform.hpp"
#include "../physics/field/field.hpp"
#include "../game/game.hpp"

class Scene: public InputContext, public Transform {
public:
    explicit Scene(const std::string &name);
    Scene(json j, int dummy);

    [[nodiscard]] const std::string &get_name() const;

    void add_field(ForceField *field);
    [[nodiscard]] const std::vector<ForceField *> &get_fields() const;

    [[nodiscard]] bool is_insubstantial() const;

    void set_active_camera(const std::string &name);
    void add_camera(Camera *cam);
    Camera *new_camera(const std::string &name);
    void remove_camera(const std::string &name);
    [[nodiscard]] Camera *get_active_camera() const;
    [[nodiscard]] Camera *get_camera(const std::string &name) const;

    template<typename T>
    void set_state_value(const std::string &name, const T &value)
    {
        Game::ref().set_state_value(this->_name, name, value);
    }

    template<typename T>
    T get_state_value(const std::string &name)
    {
        return Game::ref().get_state_value<T>(this->_name, name);
    }

    json serialise() override;

protected:
    bool _insubstantial;

private:
    std::vector<ForceField *> _fields;
    std::string _name;
    std::map<std::string, Camera *> _cameras;
    Camera *_active_camera;
};