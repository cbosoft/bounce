#pragma once
#include <chrono>
#include <vector>

#include "../collider/collider.hpp"
#include "../rigidbody/rigidbody.hpp"
#include "../field/field.hpp"
#include "../material/material.hpp"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::ratio<1, 1>> Duration;

struct CollisionInformation {
    Rigidbody *b;
    arma::vec2 normal;
    arma::vec2 at;
    double when;
    CollisionDirection adir, bdir;
};

class Game;
class PhysicsEngine {
public:
    static PhysicsEngine &ref();
    ~PhysicsEngine();

    void timestep();
    void timestep_objects();
    void resolve_collision(Rigidbody *a, Rigidbody *b, const arma::vec2 &normal);

    static PhysicsMaterial get_overall_material_properties(const PhysicsMaterial &a, const PhysicsMaterial &b);
    void check_set_time();
    void set_timescale(double v);
    [[nodiscard]] double get_time() const;
    [[nodiscard]] double get_dt() const;

    [[nodiscard]] bool check_will_collide(const Rigidbody *a, const Rigidbody *b, CollisionInformation &ci) const;

private:
    void resolve_collision_free_bodies(Rigidbody *a, Rigidbody *b, const arma::vec2 &normal);
    void resolve_collision_one_fixed(Rigidbody *free_body, Rigidbody *fixed_body, const arma::vec2 &normal);

    [[nodiscard]] bool check_will_collide_circle_circle(const Rigidbody *a, const Rigidbody *b, CollisionInformation &ci) const;
    [[nodiscard]] bool check_will_collide_circle_rect(const Rigidbody *circle, const Rigidbody *rect, CollisionInformation &ci) const;
    [[nodiscard]] bool check_will_collide_rect_rect(const Rigidbody *a, const Rigidbody *b, CollisionInformation &ci) const;

    PhysicsEngine();

    double dt, time, irl_time, timescale;
    Clock::time_point epoch;
};
