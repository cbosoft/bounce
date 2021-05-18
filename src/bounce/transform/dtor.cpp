#include <bounce/transform/transform.hpp>
#include <bounce/game/game.hpp>

void Transform::destroy()
{
    if (this->_parent)
        this->_parent->remove_child(this);

    // need to copy child list, as children remove themselves from master list in Transform::destroy();
    std::list<Transform *> children_copy = this->_children;
    for (auto *child : children_copy) {
        child->destroy();
    }
    Game::ref().add_to_graveyard(this);
}