#pragma once

#include "../scene.hpp"

class BounceEngineLogoSplash : public Scene {
public:
    BounceEngineLogoSplash(const std::string &scene_target_after, const std::string &font="DOS_VGA_437");
};

class AnimatedBounceIcon final: public RectangleMeshRenderable {
public:
    AnimatedBounceIcon();

    void on_update() override;

private:
    double dtheta;
};
