#pragma once
#include <chrono>
#include <vector>

#include "../../object/object.hpp"
#include "../field/field.hpp"
#include "../shape/shape.hpp"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<double, std::ratio<1, 1>> Duration;

typedef struct {
    bool happens;
    arma::vec2 normal;
    arma::vec2 at;
} CollisionInformation;

class Game;
class PhysicsEngine {
public:
    static PhysicsEngine &ref();
    ~PhysicsEngine();

    void timestep();
    void timestep_objects();
    CollisionInformation &resolve_collision(Object *a, Object *b);
    CollisionInformation &resolve_collision_free_bodies(Object *a, Object *b);
    CollisionInformation &resolve_collision_one_fixed(Object *free_body, Object *fixed_body);

    static double get_overall_cor(double cora, double corb);
    void check_set_time();
    void set_timescale(double v);
    double get_time() const;
    double get_dt() const;

    void register_object(Object *obj);
    void unregister_object(Object *obj);
    std::list<Object *> get_active_objects() const;

    bool check_will_collide(const Object *a, const Object *b, arma::vec2 &norm, arma::vec2 &at);

private:
    bool check_will_collide_circle_circle(const Object *a, const Object *b, arma::vec2 &norm, arma::vec2 &at);
    bool check_will_collide_circle_rect(const Object *circle, const Object *rect, arma::vec2 &norm, arma::vec2 &at);
    bool check_will_collide_rect_rect(const Object *a, const Object *b, arma::vec2 &norm, arma::vec2 &at);

    void traverse_get_objects(Transform *t, std::list<Object *> &out) const;

    PhysicsEngine();

    double dt, time, irl_time, timescale;
    Clock::time_point epoch;
    CollisionInformation _cached_collision;
    std::list<Object *> _all_objects;
    static constexpr double COLLISION_THRESH = 5e-2;
};
