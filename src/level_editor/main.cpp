#include <bounce/bounce.hpp>

#include "editor/editor.hpp"


int main()
{
    auto &game = Game::setup("bounce-demo");
    Renderer &r = Renderer::get();
    r.set_max_fps(60);
    r.define_shader("default", "vertex/vertex", "fragment/fragment");
    r.define_shader("sprite", "vertex/vertex", "fragment/sprite");
    r.define_shader("font", "vertex/vertex", "fragment/font");
    r.define_shader("star", "vertex/vertex", "fragment/star");

    r.define_screen_effect_shader("default", "vertex/quad", "fragment/quad");
    r.define_screen_effect_shader("1bit", "vertex/quad", "fragment/ordered_dithering");
    r.define_screen_effect_shader("crt", "vertex/quad", "fragment/crt");

    //r.set_screen_effect("1bit");
    //r.set_screen_effect("crt");

    //game.add_scene(new BounceEngineLogoSplash("level editor"));
    game.add_scene(new LevelEditor());

    game.run();
    return 0;
}
