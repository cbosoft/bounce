#include "game.hpp"

void Game::physics_step()
{
  this->time += this->dt;
  for (auto *obj : this->objects) {
    obj->timestep(this->dt, this->g);
  }

  for (size_t i = 0; i < this->objects.size(); i++) {
    for (size_t j = 0; j < this->objects.size(); j++) {
      if (j >= i) break;

      auto *o1 = this->objects[i], *o2 = this->objects[j];

      arma::vec2 norm;
      if (o1->will_collide(o2, norm)) {
        if (o1->fixed() || o2->fixed()) {
          auto *free_body = (o2->fixed()?o1:o2);
          double m = (o2->fixed()?1.0:-1.0);
          double vmag = arma::norm(free_body->velocity);
          free_body->velocity = norm * vmag * m;
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
