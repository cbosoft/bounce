#pragma once
#include <chrono>
#include <vector>

#include "../../object/object.hpp"
#include "../field/field.hpp"
#include "../shape/shape.hpp"
#include "../material/material.hpp"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::ratio<1, 1>> Duration;

struct CollisionInformation {
    Object *b;
    arma::vec2 normal;
    arma::vec2 at;
    double when;
};

class Game;
class PhysicsEngine {
public:
    static PhysicsEngine &ref();
    ~PhysicsEngine();

    void timestep();
    void timestep_objects();
    void resolve_collision(Object *a, Object *b, const arma::vec2 &normal);
    void resolve_collision_free_bodies(Object *a, Object *b, const arma::vec2 &normal);
    void resolve_collision_one_fixed(Object *free_body, Object *fixed_body, const arma::vec2 &normal);

    static PhysicsMaterial get_overall_material_properties(const PhysicsMaterial &a, const PhysicsMaterial &b);
    void check_set_time();
    void set_timescale(double v);
    double get_time() const;
    double get_dt() const;

    void register_object(Object *obj);
    void unregister_object(Object *obj);
    std::list<Object *> get_active_objects() const;

    bool check_will_collide(const Object *a, const Object *b, arma::vec2 &norm, arma::vec2 &at, double &when);

private:
    bool check_will_collide_circle_circle(const Object *a, const Object *b, arma::vec2 &norm, arma::vec2 &at, double &when);
    bool check_will_collide_circle_rect(const Object *circle, const Object *rect, arma::vec2 &norm, arma::vec2 &at, double &when);
    bool check_will_collide_rect_rect(const Object *a, const Object *b, arma::vec2 &norm, arma::vec2 &at, double &when);

    void traverse_get_objects(Transform *t, std::list<Object *> &out) const;

    PhysicsEngine();

    double dt, time, irl_time, timescale;
    Clock::time_point epoch;
    std::list<Object *> _all_objects;
};
