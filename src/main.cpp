#include "game/game.hpp"
#include "physics/field/force_fields.hpp"

int main()
{
  Game game;
  auto &pe = PhysicsEngine::engine();
  pe.add_field(new UnboundedLinearForceField(0, 0, 0, -10));

  game.run();
  return 0;
}
