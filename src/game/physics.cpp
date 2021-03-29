#include "game.hpp"

void Game::physics_init()
{
  this->physics_epoch = Clock::now();
}

double Game::check_time()
{
  Clock::time_point now = Clock::now();
  Duration delta = (now - this->physics_epoch);
  this->irl_time =  delta.count()*this->time_scale;
  return this->irl_time;
}

void Game::physics_step()
{
  this->check_time();
  while (this->physics_time < this->irl_time) {
    this->physics_timestep_objects();
  }
}

void Game::physics_timestep_objects()
{
  this->physics_time += this->dt;
  for (auto *obj : this->objects) {
    obj->timestep(this->dt, this->g);
  }

  for (size_t i = 0; i < this->objects.size(); i++) {
    for (size_t j = 0; j < this->objects.size(); j++) {
      if (j >= i) break;

      auto *o1 = this->objects[i], *o2 = this->objects[j];
      if (o1->fixed() && o2->fixed()) continue;

      arma::vec2 norm;
      if (o1->will_collide(o2, norm)) {
        if (o1->fixed() || o2->fixed()) {
          auto *free_body = (o2->fixed()?o1:o2);

          const arma::vec &v = free_body->velocity;
          double n2 = arma::dot(norm, norm);
          double vn = arma::dot(v, norm);
          arma::vec2 vel_parallel_to_norm = (vn/n2)*norm;
          // if (vel_parallel_to_norm[0]*v[0] < 0)
          //   vel_parallel_to_norm *= -1.0;
          arma::vec2 vel_perpendicular_to_norm = v - vel_parallel_to_norm;

          double e = 0.5, f=e;
          vel_parallel_to_norm *= e; // energy lost to heat, sound
          vel_perpendicular_to_norm *= f; //energy lost to friction

          arma::vec2 new_vel = vel_perpendicular_to_norm - vel_parallel_to_norm;
          std::cerr
            << n2 << " "
            << vn << " "
            << "(" << norm[0] << ", " << norm[1] << ") "
            << "(" << vel_parallel_to_norm[0] << ", " << vel_parallel_to_norm[1] << ") "
            << "(" << new_vel[0] << ", " << new_vel[1] << ") "
            << std::endl;
          free_body->velocity = new_vel;
          free_body->new_position = free_body->velocity*dt + free_body->position;
        }
        else {
          // TODO
        }
      }
    }
  }

  for (auto *obj : this->objects) {
    obj->accept_position();
  }
}
