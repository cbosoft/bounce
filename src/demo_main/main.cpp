#include "../engine/bounce.hpp"

#include "main_menu.hpp"
#include "demo_space_shooter/free_roam.hpp"
#include "demo_platformer/platformer.hpp"


int main()
{
    auto &game = Game::ref();
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
    //r.set_screen_effect("crt");

    game.add_scene(new DemoMainMenu());
    game.add_scene(new DemoSpaceShooter());
    game.add_scene(new DemoPlatformer());
    game.run();
    return 0;
}
