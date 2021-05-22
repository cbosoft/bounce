#include <bounce/renderer/renderable/renderable.hpp>
#include <bounce/physics/engine/engine.hpp>

void Renderable::on_update() {
    if (this->_animated) {
        double now = PhysicsEngine::ref().get_time();
        if (now - this->_time_last_frame_advance >= this->_animation_period) {
            this->_current_frame++;
            if (this->_current_frame > this->_current_texture_loop.to) {
                this->_current_frame = this->_current_texture_loop.from;
                this->_has_completed_loop_once = true;
            }
            this->_time_last_frame_advance = now;
        }
    }
}