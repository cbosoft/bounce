#pragma once

#include <list>
#include <map>
#include <string>
#include <armadillo>

class Renderable;
class Transform {
public:
    Transform();
    Transform(Transform *parent);
    Transform(Transform *parent, const arma::vec2 &position);
    virtual ~Transform() =default;
    void destroy();

    const arma::vec2 &get_relative_position() const;
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
    void deactivate();
    bool is_active() const;

    virtual void attach_renderable(const std::string &name, Renderable *rbl);
    virtual void attach_renderable(Renderable *rbl);
    virtual void get_renderables(std::list<const Renderable *> &out) const;

    void update();
    virtual void on_update() {}

    [[nodiscard]] virtual bool is_physics_object() const { return false; }

private:
    Transform *_parent;
    arma::vec2 _relative_position;
    bool _active;

    std::list<Transform *> _children;
    std::map<std::string, Renderable *> _named_renderables;
    std::list<Renderable *> _anonymous_renderables;
};