#include "../common/game/game.hpp"
#include "../common/scene/scene.hpp"
#include "../common/scene/menu/menu.hpp"
#include "../common/scene/menu/menuitem/menuitem.hpp"
#include "../common/renderer/renderables.hpp"
#include "../version.hpp"

class MenuButton : public MenuItem
{
public:
    MenuButton(Menu *parent, const std::string &label)
        : MenuItem(parent)
    {
        auto *col = new CollectionRenderable();
        this->bg = MeshRenderable::filleted_rectangle(20, 5, 3);
        col->add_child(bg);
        auto *msh= MeshRenderable::filleted_rectangle(21, 5, 3);
        msh->set_scale(19.0);
        msh->set_colour(Colour::from_rgb(0, 0, 0));
        col->add_child(msh);
        auto *txt = new TextRenderable(label, "../resources/BebasNeue-Regular.ttf", 80);
        col->add_child(txt);
        txt->set_relative_position({-15, -3});
        this->set_renderable(col);
    }

    void highlight() override {
        this->bg->set_colour(Colour::from_rgb(155, 200, 250));
    }

    void unhighlight() override {
        this->bg->set_colour(Colour::from_rgb(127, 127, 127));
    }

    void action() override {};

private:
    Renderable *bg;
};

class DemoMenu : public Menu {
public:
    explicit DemoMenu(Game *game)
        : Menu(game, "menu")
    {
        this->set_repeat_delay(300);
        Renderer::get().set_camera_target(this);
        auto *a = new MenuButton(this, "continue");
        a->set_position({50, 50});
        this->add_item(a);

        auto *b = new MenuButton(this, "new");
        b->set_position({50, 0});
        this->add_item(b);
        b->connect_up(a);

        auto *c = new MenuButton(this, "quit");
        c->set_position({50, -50});
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
        //Renderer::get().set_camera_target(o);
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
