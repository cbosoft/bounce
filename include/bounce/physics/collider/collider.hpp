#pragma once

#include "../../transform/transform.hpp"
#include "../../serialisation/json.hpp"
#include "../../renderer/renderable/renderable.hpp"
#include "../../renderer/renderable/mesh/mesh.hpp"

enum ShapeType {ST_CIRCLE, ST_RECT};
enum CollisionDirection {CD_TOP, CD_LEFT, CD_BOTTOM, CD_RIGHT};

class Collider : public Transform {
public:
    explicit Collider(Transform *parent);
    explicit Collider(json j);

    void on_update() override;
    virtual void on_collision(Collider *other) {}
    void get_renderables(std::list<const Renderable *> &out) const override;

    void set_shape_rectangle(double w, double h);
    void set_shape_circle(double radius);
    void get_rect_half_extents(double &hw, double &hh) const;
    void get_circle_radius(double &r) const;
    [[nodiscard]] ShapeType get_shape_type() const;

    void set_interaction_mask(unsigned int mask);
    [[nodiscard]] bool can_interact() const;
    [[nodiscard]] unsigned int get_interaction_mask() const;
    [[nodiscard]] bool does_interact_with(const Collider *other) const;
    [[nodiscard]] bool does_interact_with(unsigned int mask) const;

    void set_touching(CollisionDirection dir);
    void set_not_touching(CollisionDirection dir);
    void set_not_touching_anything();
    [[nodiscard]] bool is_touching(CollisionDirection dir) const;
    [[nodiscard]] bool is_touching_top() const;
    [[nodiscard]] bool is_touching_left() const;
    [[nodiscard]] bool is_touching_bottom() const;
    [[nodiscard]] bool is_touching_right() const;

    json serialise() override;

protected:
    double _hw, _hh;
    ShapeType _shape_type;
    unsigned int _touching_flags;
    unsigned int _interaction_mask;
    MeshRenderable *_renderable_collider;
};