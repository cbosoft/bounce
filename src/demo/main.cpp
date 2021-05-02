#include <bounce/bounce.hpp>

#include "main_menu.hpp"
#include "demo_space_shooter/free_roam.hpp"
#include "demo_space_shooter/tut_menu.hpp"
#include "demo_platformer/platformer.hpp"
#include "demo_music/music.hpp"


int main()
{
    auto &game = Game::setup("bounce-demo");
    Renderer &r = Renderer::get();
    r.set_max_fps(100);
    r.define_shader("default", "vertex/vertex", "fragment/fragment");
    r.define_shader("sprite", "vertex/vertex", "fragment/sprite");
    r.define_shader("font", "vertex/vertex", "fragment/font");
    r.define_shader("star", "vertex/vertex", "fragment/star");

    r.define_screen_effect_shader("default", "vertex/quad", "fragment/quad");
    r.define_screen_effect_shader("1bit", "vertex/quad", "fragment/ordered_dithering");
    r.define_screen_effect_shader("crt", "vertex/quad", "fragment/crt");

    //r.set_screen_effect("1bit");
    r.set_screen_effect("crt");

    r.set_shader_variable("1bit", "dark_colour", arma::vec4({0, 0, 0, 255}));
    r.set_shader_variable("1bit", "light_colour", arma::vec4({255, 255, 255, 255}));

    game.add_scene(new DemoMainMenu());
    game.add_scene(new DemoSpaceShooter());
    game.add_scene(new DemoPlatformer());
    game.add_scene(new DemoSpaceShooterTutorialMenu());
    game.add_scene(new DemoMusic());

    game.run();
    return 0;
}
