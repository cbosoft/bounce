#pragma once
#include <chrono>
#include <vector>

#include "../../object/object.hpp"
#include "../field/field.hpp"

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
    static PhysicsEngine &init_engine(Game *game, double dt, double timescale);
    static PhysicsEngine &engine();
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

private:
    PhysicsEngine(Game *game, double dt, double timescale);

    Game *game;

    double dt, time, irl_time, timescale;
    Clock::time_point epoch;
    CollisionInformation _cached_collision;
    std::list<Object *> _all_objects;
};
