#include <bounce/renderer/renderer.hpp>
#include <bounce/game/game.hpp>
#include <bounce/scene/scene.hpp>

/**
 * Convert a screen position into world units based on the position and size of the current camera as well as the window
 * size
 * .
 * @param screen_pos Position in screen coords.
 * @return Position in world coords.
 */
arma::vec2 Renderer::screen_pos_to_world_pos(const arma::vec2 &screen_pos) const
{
    arma::vec2 flipped = screen_pos;
    flipped[1] = this->window_size[1] - flipped[1];
    arma::vec2 uv = (flipped - this->window_size*0.5) / this->window_size;
    auto *cam = this->game->get_active_scene()->get_active_camera();
    return (uv % cam->get_size()*2.) + cam->get_position();
}