#include "animated_mesh.hpp"

void AnimatedMeshRenderable::animate_to(MeshRenderable *target_mesh, int n_frames)
{
    this->set_target_get_gradients(target_mesh->_points, target_mesh->get_size(), target_mesh->get_angle(), n_frames);
}

void AnimatedMeshRenderable::animate_to_original(int n_frames)
{
    this->set_target_get_gradients(this->_original_points, this->_original_size, this->_original_angle, n_frames);
}

void AnimatedMeshRenderable::set_target_get_gradients(const std::vector<arma::vec2> &target, const arma::vec2 &size, double angle, int n_frames)
{
    auto n = int(target.size()), cn = int(this->_points.size());
    this->_target_points = target;

    if (n == cn) {
        // same size, no interpolation necessary
    }
    else if (n > cn) {
        // new shape has more vertices
        const arma::vec2 &endp = this->_points.back();
        for (int i = cn; i < n; i++) {
            this->_points.push_back(endp);
        }
    }
    else {
        // old shape has more vertices
        const arma::vec2 &endp = target.back();
        for (int i = n; i < cn; i++) {
            this->_target_points.push_back(endp);
        }
    }

    assert(this->_points.size() == this->_target_points.size());


    this->_gradients.clear();
    auto df = double(n_frames);
    bool all_zero = true;
    constexpr double eps = 1e-10;
    for (size_t i = 0; i < this->_target_points.size(); i++) {
        arma::vec2 dr = this->_target_points[i] - this->_points[i];
        this->_gradients.emplace_back(dr/df);
        all_zero = all_zero && std::abs(dr[0]) < eps && std::abs(dr[1]) < eps;
    }
    this->_scale_grad = (size - this->get_size())/df;
    this->_angle_grad = (angle - this->get_angle())/df;
    all_zero = all_zero && arma::sum(arma::abs(this->_scale_grad)) < eps;

    this->_movement_frames_left = all_zero ? 0 : n_frames;
}

void AnimatedMeshRenderable::step_animation()
{
    this->_movement_frames_left --;
    for (size_t i = 0; i < this->_points.size(); i++)
        this->_points[i] += this->_gradients[i];
    this->set_size(this->get_size() + this->_scale_grad);
    this->set_angle(this->get_angle() + this->_angle_grad);
}

void AnimatedMeshRenderable::on_update()
{
    if (this->_movement_frames_left)
        this->step_animation();
}