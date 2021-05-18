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

    virtual json serialise();

    [[nodiscard]] bool is_a(const std::string &tag) const;
    [[nodiscard]] bool is_a(std::size_t tag_hash) const;
    void add_tag(const std::string &tag);
    void add_tag(const std::size_t);
    void find_in_children(const std::string &tag, std::list<Transform *> &out) const;
    void find_in_children(std::size_t tag_hash, std::list<Transform *> &out) const;

    template<typename T>
    void find_in_children_cast(const std::string &tag, std::list<T> &out) const
    {
        this->template find_in_children_cast<T>(std::hash<std::string>{}(tag), out);
    }

    template<typename T>
    void find_in_children_cast(std::size_t tag_hash, std::list<T> &out) const
    {
        std::list<Transform *> transforms;
        this->find_in_children(tag_hash, transforms);
        for (auto *transform: transforms) {
            out.push_back((T)transform);
        }
    }

private:
    Transform *_parent;
    arma::vec2 _relative_position;
    bool _active;
    double _scale;
    int _relative_z;

    std::list<Transform *> _children;
    std::list<std::string> _tags;
    std::list<std::size_t> _tag_hashes;
};