#include "../common/bounce.hpp"
#include "../version.hpp"

#include "main_menu.hpp"
#include "free_roam.hpp"
#include "boid_sim.hpp"


int main()
{
    std::cerr << GitMetadata::version_string() << std::endl;
    Game game(1280, 960);
    Renderer &r = Renderer::get();
    r.set_max_fps(100);
    r.define_shader("default", "vertex/vertex", "fragment/fragment");
    r.define_shader("sprite", "vertex/vertex", "fragment/sprite");
    r.define_shader("font", "vertex/vertex", "fragment/font");
    r.define_shader("star", "vertex/vertex", "fragment/star");

    r.define_screen_effect_shader("default", "vertex/quad", "fragment/ordered_dithering");

    game.add_scene(new MainMenu(&game));
    game.add_scene(new FreeRoamScene(&game));
    game.add_scene(new BoidScene(&game));
    game.run();
    return 0;
}
