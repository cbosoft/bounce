#pragma once

#include <map>
#include <string>
#include "../input/context/context.hpp"
#include "../object/object.hpp"
#include "../transform/transform.hpp"
#include "../transform/rect/rect.hpp"
#include "../physics/field/field.hpp"
#include "../game/game.hpp"

class Scene: public InputContext, public Transform {
public:
    explicit Scene(const std::string &name);

    [[nodiscard]] const std::string &get_name() const;
    std::vector<Object *> find_objects_near_to(Transform *t, double radius) const;

    void add_field(ForceField *field);
    [[nodiscard]] const std::vector<ForceField *> &get_fields() const;

    [[nodiscard]] bool is_insubstantial() const;

    void set_active_camera(const std::string &name);
    void add_camera(const std::string &name, RectTransform *t);
    RectTransform *new_camera(const std::string &name);
    void remove_camera(const std::string &name);
    RectTransform *get_active_camera() const;

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

protected:
    bool _insubstantial;

private:
    std::vector<ForceField *> _fields;
    std::string _name;
    std::map<std::string, RectTransform *> _cameras;
    RectTransform *_active_camera;
};