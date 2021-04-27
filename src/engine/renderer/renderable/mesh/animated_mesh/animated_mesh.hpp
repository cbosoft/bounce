#pragma once

#include "../mesh.hpp"

class AnimatedMeshRenderable : public MeshRenderable {
public:
    explicit AnimatedMeshRenderable(MeshRenderable *init);

    void animate_to(MeshRenderable *target, int n_frames);
    void animate_to_original(int n_frames);

    void on_update() override;

protected:

    void step_animation();
    void set_target_get_gradients(const std::vector<arma::vec2> &target, const arma::vec2 &size, double angle, int n_frames);
    int _movement_frames_left;
    double _original_angle, _angle_grad;
    arma::vec2 _original_size, _scale_grad;
    const std::vector<arma::vec2> _original_points;
    std::vector<arma::vec2> _target_points, _gradients;
};