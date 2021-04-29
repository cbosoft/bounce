#pragma once
#include <armadillo>
#include <vector>

#include "../transform/transform.hpp"
#include "../colour/colour.hpp"
#include "../renderer/renderables.hpp"
#include "../physics/shape/shape.hpp"

class Object : public Transform {
  public:
    Object(Transform *parent);
    Object(Transform *parent, const arma::vec2 &position, bool fixed=false, double cor=1.0);
    Object(Transform *parent, const arma::vec2 &position, double mass, double cor=1.0);
    ~Object();

    virtual void physics_update() {}

    void timestep(double dt);

    void accept_position();

    void set_mass(double mass);
    double get_mass() const;

    bool fixed() const;

    const Colour &get_colour() const;
    void set_colour(const Colour &colour);

    const arma::vec2 &get_new_position() const;
    const arma::vec2 &get_velocity() const;
    const arma::vec2 &get_force() const;

    void set_position(const arma::vec2 &position) override;
    void set_new_position(const arma::vec2 &new_position);
    void set_new_position(const arma::vec2 &&new_position);
    void set_velocity(const arma::vec2 &new_position);
    void set_velocity(const arma::vec2 &&new_position);
    void set_force(const arma::vec2 &force);
    void set_force(const arma::vec2 &&force);
    void add_force(const arma::vec2 &force);

    double get_cor() const;
    void set_cor(double _cor);

    void attach_renderable(const std::string &name, Renderable *rbl) override;
    void attach_renderable(Renderable *rbl) override;

    void set_layer(const std::string &layer);
    const std::string &get_layer() const;

    virtual void on_collision(Object *other) {}

    [[nodiscard]] bool is_physics_object() const override { return true; }
    void get_renderables(std::list<const Renderable *> &out) const override;

    [[nodiscard]] const CollisionShape &get_shape() const;
    void set_shape(const CollisionShape &shape);

  private:
    CollisionShape _shape;
    arma::vec2 new_position;
    arma::vec2 velocity;
    arma::vec2 force;

    double mass, inv_mass, cor;
    std::string _layer;

    Colour c;

    bool _fixed;
    MeshRenderable *_renderable_collider;
};
