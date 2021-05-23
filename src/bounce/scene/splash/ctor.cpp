#include <bounce/scene/splash/splash.hpp>
#include <bounce/game/game.hpp>
#include <bounce/events.hpp>
#include <bounce/physics/rigidbody/rigidbody.hpp>
#include <bounce/renderer/renderable/text/text.hpp>

BounceEngineLogoSplash::BounceEngineLogoSplash(const std::string &target, const std::string &font)
:   Scene("bounce engine logo")
{
    Game::ref().add_event(new DelayRunOtherEvent(3500, new PushSceneTransitionEvent(target)));

    auto *bounce = new Rigidbody(this);
    auto *icon = new AnimatedBounceIcon();
    icon->set_parent(bounce);
    bounce->set_position({0, 200});
    bounce->set_velocity({0, -80});
    bounce->set_shape_rectangle(10, 10);

    auto *eng = new Rigidbody(this);
    auto *txt = new TextRenderable("bounce by cbo", font, 150);
    txt->set_parent(eng);
    eng->set_position({0, -5});
    eng->set_shape_rectangle(10, 10);

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
