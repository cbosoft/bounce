#pragma once

#include <list>
#include <map>
#include <string>
#include <armadillo>

#include "../serialisation/json.hpp"

class Renderable;
class Transform {
public:
    Transform();
    explicit Transform(Transform *parent);
    Transform(Transform *parent, const arma::vec2 &position);
    explicit Transform(json j);
    virtual ~Transform() =default;
    void destroy();

    arma::vec2 get_relative_position() const;
    arma::vec2 get_position() const;

    virtual void set_relative_position(const arma::vec2 &relative_position);
    virtual void set_position(const arma::vec2 &position);

    const Transform *get_root() const;
    void set_parent(Transform *parent);
    Transform *get_parent() const;
    void remove_child(Transform *child);
    void add_child(Transform *child);
    const std::list<Transform *> &get_children() const;
    unsigned long count() const;

    void activate();
    virtual void on_activate() {}
    void deactivate();
    virtual void on_deactivate() {}
    bool is_active() const;

    void set_scale(double scale);
    double get_scale() const;

    void set_z(int z);
    void set_relative_z(int rel_z);
    int get_z() const;
    int get_relative_z() const;

    virtual void get_renderables(std::list<const Renderable *> &out) const;

    void update();
    virtual void on_update() {}

    [[nodiscard]] virtual bool is_physics_object() const { return false; }

    json serialise();

private:
    Transform *_parent;
    arma::vec2 _relative_position;
    bool _active;
    double _scale;
    int _relative_z;

    std::list<Transform *> _children;
};