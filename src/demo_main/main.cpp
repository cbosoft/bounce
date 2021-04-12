#include "../common/game/game.hpp"
#include "../common/scene/scene.hpp"
#include "../common/scene/menu/menu.hpp"
#include "../common/scene/menu/menuitem/menuitem.hpp"
#include "../common/renderer/renderables.hpp"
#include "../version.hpp"

class MenuButton : public MenuItem
{
public:
    explicit MenuButton(Menu *parent)
        : MenuItem(parent)
    {
        auto *rbl = MeshRenderable::filleted_rectangle(10, 5, 1);
        rbl->set_scale(5);
        this->set_renderable(rbl);
    }

    void action() override {};
};

class DemoMenu : public Menu {
public:
    explicit DemoMenu(Game *game)
        : Menu(game, "menu")
    {
        this->set_repeat_delay(300);
        auto *a = new MenuButton(this);
        this->add_item(a);

        auto *b = new MenuButton(this);
        b->set_position({0, -3});
        this->add_item(b);
        b->connect_up(a);

        auto *c = new MenuButton(this);
        c->set_position({0, -6});
        this->add_item(c);
        c->connect_up(b);

        c->connect_down(a);
        this->set_selected(a);

    }

    void back() override { this->get_game()->quit(); };
};

class DemoScene : public Scene {
public:
    explicit DemoScene(Game *game)
        : Scene(game, "scene")
        , player(nullptr)
    {
        auto *o = new PhysicsObject(this, {0, 0}, false);
        o->set_radius(10.0);
        //o->set_renderable(new CircleRenderable());
        o->set_renderable(MeshRenderable::rectangle(10, 5));
        o->set_layer("other");
        this->add_object(o);

        o = new PhysicsObject(this, {0, 0}, false, 0.5);
        o->set_radius(4.0);
        o->set_colour(Colour::from_rgb_f(0.5, 0.5, 0.5));
        o->set_renderable(MeshRenderable::regular_polygon(5));
        this->add_object(o);

        o = new PhysicsObject(this, {30, 0}, false, 0.5);
        o->set_radius(4.0);
        o->set_colour(Colour::from_rgb_f(0.5, 0.5, 0.5));
        o->set_renderable(MeshRenderable::filleted_rectangle(5, 10, 1));
        this->add_object(o);
        this->set_player(o);
    }

    void up() override { this->player->add_force({0, 1e3}); }
    void left() override { this->player->add_force({-1e3, 0}); }
    void down() override { this->player->add_force({0, -1e3}); }
    void right() override { this->player->add_force({1e3, }); }

    void action() override {}
    void alternate() override {}

    void back() override { this->get_game()->quit(); }

private:

    void set_player(PhysicsObject *o)
    {
        this->player = o;
        Renderer::get().set_camera_target(o);
    }

    PhysicsObject *player;
};

int main()
{
    std::cerr << GitMetadata::version_string() << std::endl;
    Game game(1280, 960);
    Scene *scene = new DemoMenu(&game);
    game.add_scene(scene);
    scene = new DemoScene(&game);
    game.add_scene(scene);
    game.run();
    return 0;
}
