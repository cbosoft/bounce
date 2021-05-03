#include <bounce/scene/splash/splash.hpp>
#include <bounce/game/game.hpp>
#include <bounce/events.hpp>

BounceEngineLogoSplash::BounceEngineLogoSplash(const std::string &target, const std::string &font)
:   Scene("bounce engine logo")
{
    Game::ref().add_event(new DelayRunOtherEvent(3500, new PushSceneTransitionEvent(target)));

    auto *bounce = new Object(this);
    bounce->attach_renderable(new AnimatedBounceIcon());
    bounce->set_position({0, 200});
    bounce->set_velocity({0, -80});
    bounce->set_shape(CollisionShape::rectangle(10, 10));

    auto *eng = new Object(this);
    eng->attach_renderable(new TextRenderable("bounce by cbo", font, 150));
    eng->set_position({0, -5});
    eng->set_shape(CollisionShape::rectangle(10, 10));

}

AnimatedBounceIcon::AnimatedBounceIcon()
:   RectangleMeshRenderable(20, 20)
,   dtheta(0.01)
{
    this->set_texture_name("cbo_icon");
}

void AnimatedBounceIcon::on_update()
{
    double theta = this->get_angle();
    if (std::abs(theta) > 0.3) this->dtheta *= -1.0;
    this->set_angle(theta + this->dtheta);
}
