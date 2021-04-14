#include "../common/bounce.hpp"
#include "../version.hpp"

class MenuButton : public MenuItem
{
public:
    MenuButton(Menu *parent, const std::string &label)
        : MenuItem(parent)
    {
        auto *col = new CollectionRenderable();
        this->bg = MeshRenderable::rectangle(20, 5);
        col->add_child(bg);
        auto *msh= MeshRenderable::rectangle(21, 5);
        msh->set_scale(19.0);
        msh->set_colour(Colour::from_rgb(0, 0, 0));
        col->add_child(msh);
        auto *txt = new TextRenderable(label, "../resources/BebasNeue-Regular.ttf", 80);
        col->add_child(txt);
        this->set_renderable(col);
    }

    void highlight() override {
        this->bg->set_colour(Colour::from_rgb(155, 200, 250));
    }

    void unhighlight() override {
        this->bg->set_colour(Colour::from_rgb(127, 127, 127));
    }

private:
    Renderable *bg;
};

class DemoMenu : public Menu {
public:
    explicit DemoMenu(Game *game)
        : Menu(game, "menu")
    {
        this->set_repeat_delay(300);
        auto *a = new MenuButton(this, "continue");
        a->set_position({50, 20});
        this->add_item(a);

        auto *b = new MenuButton(this, "new");
        b->set_position({50, 0});
        this->add_item(b);
        b->connect_up(a);
        b->set_callback_action(DemoMenu::new_callback);

        auto *c = new MenuButton(this, "quit");
        c->set_position({50, -20});
        this->add_item(c);
        c->connect_up(b);
        c->set_callback_action(DemoMenu::quit_callback);

        c->connect_down(a);
        this->set_selected(a);

        auto *ttl = new TextRenderable("Bounce", "../resources/BebasNeue-Regular.ttf", 150);
        ttl->set_position({-50, 0});
        ttl->set_alignment(HA_right, VA_bottom);
        ttl->set_colour(Colour::from_grayscale(40));
        this->add_floating_renderable(ttl);
        auto *ttl2 = new TextRenderable("Bounce", "../resources/BebasNeue-Regular.ttf", 175);
        ttl2->set_position({-50, 0});
        ttl2->set_colour(Colour::from_grayscale(80));
        this->add_floating_renderable(ttl2);
        auto *ttl3 = new TextRenderable("Bounce", "../resources/BebasNeue-Regular.ttf", 200);
        ttl3->set_position({-50, 0});
        ttl3->set_alignment(HA_left, VA_top);
        this->add_floating_renderable(ttl3);

    }

    static void quit_callback(MenuItem *i)
    {
        i->get_game()->quit();
    }

    static void new_callback(MenuItem *i)
    {
        i->get_game()->add_event(new PushSceneTransitionEvent("boids"));
    }

    void back() override { this->get_game()->quit(); };
};

class DemoScene : public Scene {
public:
    explicit DemoScene(Game *game)
        : Scene(game, "scene")
        , player(nullptr)
    {
        auto *o = new Object(this, {0, 0}, false);
        o->set_radius(10.0);
        //o->set_renderable(new CircleRenderable());
        o->set_renderable(MeshRenderable::rectangle(10, 5));
        o->set_layer("other");
        this->add_object(o);

        o = new Object(this, {0, 0}, false, 0.5);
        o->set_radius(4.0);
        o->set_colour(Colour::from_rgb_f(0.5, 0.5, 0.5));
        o->set_renderable(MeshRenderable::regular_polygon(5));
        this->add_object(o);

        o = new Object(this, {30, 0}, false, 0.5);
        o->set_radius(4.0);
        o->set_colour(Colour::from_rgb_f(0.5, 0.5, 0.5));
        o->set_renderable(MeshRenderable::filleted_rectangle(5, 10, 1));
        this->add_object(o);
        this->set_player(o);
        this->get_active_camera()->set_parent(o);
    }

    void up() override { this->player->add_force({0, 1e3}); }
    void left() override { this->player->add_force({-1e3, 0}); }
    void down() override { this->player->add_force({0, -1e3}); }
    void right() override { this->player->add_force({1e3, }); }

    void action() override {}
    void alternate() override {}

    void back() override { this->get_game()->add_event(new PopSceneTransitionEvent()); }

private:

    void set_player(Object *o)
    {
        this->player = o;
    }

    Object *player;
};


class Observer : public Object {
public:
    explicit Observer(Transform *parent)
    : Object(parent, {0, 0}, false)
    {
        this->set_layer("observation");
    }

    // void update() override {
    //     this->set_velocity(this->get_velocity()*0.9);
    // }
};


class BoidScene : public Scene {
public:

    explicit BoidScene(Game *game)
    : Scene(game, "boids")
    {
        auto *bound = new Object(this, {0.0, 0.0}, true);
        bound->set_renderable(new CircleRenderable());
        bound->set_radius(100);
        bound->set_colour(Colour::from_grayscale(100));
        this->add_object(bound);
        // pass
        const int n = 20;
        for (int i = 0; i < n; i ++) {
            auto di = double(i - n/2)*5.0;
            auto *boid = new Object(this, {di, di}, false);
            boid->set_renderable(new CircleRenderable());
            boid->set_velocity({di, -di});
            this->add_object(boid);
        }

        this->observer = new Observer(this);
    }

    void up() override { this->observer->add_force({0, 1e3}); }
    void left() override { this->observer->add_force({-1e3, 0}); }
    void down() override { this->observer->add_force({0, -1e3}); }
    void right() override { this->observer->add_force({1e3, 0}); }

    void action() override {}
    void alternate() override {}

    void back() override { this->get_game()->add_event(new PopSceneTransitionEvent()); }

private:

    Observer *observer;

};

int main()
{
    std::cerr << GitMetadata::version_string() << std::endl;
    Game game(1280, 960);
    Renderer &r = Renderer::get();
    r.define_shader("default", "../resources/shaders/vertex/vertex.glsl", "../resources/shaders/fragment/fragment.glsl");
    r.define_shader("sprite", "../resources/shaders/vertex/vertex.glsl", "../resources/shaders/fragment/sprite.glsl");
    r.define_shader("font", "../resources/shaders/vertex/vertex.glsl", "../resources/shaders/fragment/font.glsl");

    r.define_screen_effect_shader("default", "../resources/shaders/vertex/quad.glsl",
                                  "../resources/shaders/fragment/ordered_dithering.glsl");
    Scene *scene = new DemoMenu(&game);
    game.add_scene(scene);
    scene = new DemoScene(&game);
    game.add_scene(scene);
    scene = new BoidScene(&game);
    game.add_scene(scene);
    game.run();
    return 0;
}
