#pragma once

#include "../../../engine/bounce.hpp"
#include "../player/player.hpp"


class DemoPlatformer final : public Scene {
public:
    DemoPlatformer();

    void on_activate() override;
    void on_deactivate() override;

    void back_pressed() override;

    void left_pressed() override;
    void left_released() override;
    void right_pressed() override;
    void right_released() override;
    void action_pressed() override;

private:
    DemoPlatformerPlayer *player;
};