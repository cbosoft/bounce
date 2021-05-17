#include <bounce/game/game.hpp>
#include <bounce/serialisation/deserialiser/deserialiser.hpp>

void Game::set_deserialiser(Deserialiser *deserialiser)
{
    this->_deserialiser = deserialiser;
}

Transform *Game::deserialise(json j)
{
    if (this->_deserialiser == nullptr) {
        this->_deserialiser = new Deserialiser();
    }

    return this->_deserialiser->deserialise(std::move(j));
}