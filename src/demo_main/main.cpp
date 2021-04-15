#include "../common/bounce.hpp"
#include "../version.hpp"

#define DEFAULT_FONT "DOS_VGA_437"

class MenuButton : public MenuItem
{
public:
    MenuButton(Menu *parent, const std::string &label)
        : MenuItem(parent)
    {
        auto *col = new CollectionRenderable();
        this->bg = MeshRenderable::rectangle(25, 5);
        col->add_child(bg);
        auto *msh= MeshRenderable::rectangle(26, 5);
        msh->set_scale(24);
        msh->set_colour(Colours::black);
        col->add_child(msh);
        auto *txt = new TextRenderable(label, DEFAULT_FONT, 80);
        col->add_child(txt);
        this->set_renderable(col);
    }

    void highlight() override {
        this->bg->show();
    }

    void unhighlight() override {
        this->bg->hide();
    }

private:
    Renderable *bg;
};

class DemoMenu : public Menu {
public:
    explicit DemoMenu(Game *game)
        : Menu(game, "menu")
    {
        {
            auto *b = new MenuButton(this, "physics sim");
            b->set_position({50, 15});
            this->add_item(b);
            b->set_callback_action(DemoMenu::sim_callback);
        }
        {
            auto *b = new MenuButton(this, "free roam");
            b->set_position({50, 0});
            this->add_item(b);
            b->set_callback_action(DemoMenu::free_roam_callback);
        }
        {
            auto *b = new MenuButton(this, "quit");
            b->set_position({50, -15});
            this->add_item(b);
            b->set_callback_action(DemoMenu::quit_callback);
        }

        this->connect_vertical();

        // draw logo
        {
            auto *ttl = new Object(this, {-60, 10});
            ttl->set_renderable(new TextRenderable("Bounce", DEFAULT_FONT, 150));
            ttl->set_colour(Colour::from_grayscale(40));
            ttl->set_layer("title 1");
            this->add_object(ttl);
            auto *brk = new Object(this, {-60, 0}, true);
            brk->set_layer("title 1");
            this->add_object(brk);
        }
        {
            auto *ttl = new Object(this, {-55, 5});
            ttl->set_renderable(new TextRenderable("Bounce", DEFAULT_FONT, 175));
            ttl->set_colour(Colour::from_grayscale(127));
            ttl->set_layer("title 2");
            this->add_object(ttl);
            auto *brk = new Object(this, {-55, -5}, true);
            brk->set_layer("title 2");
            this->add_object(brk);
        }
        {
            auto *ttl = new Object(this, {-50, 0});
            ttl->set_renderable(new TextRenderable("Bounce", DEFAULT_FONT, 200));
            ttl->set_colour(Colour::from_grayscale(255));
            ttl->set_layer("title 3");
            this->add_object(ttl);
            auto *brk = new Object(this, {-50, -10}, true);
            brk->set_layer("title 3");
            this->add_object(brk);
        }

        auto *gravity = new UnboundedLinearForceField(0, 0, 0, -10);
        this->add_field(gravity);
    }

    static void quit_callback(MenuItem *i)
    {
        i->get_game()->quit();
    }

    static void sim_callback(MenuItem *i)
    {
        i->get_game()->add_event(new PushSceneTransitionEvent("sim"));
    }

    static void free_roam_callback(MenuItem *i)
    {
        i->get_game()->add_event(new PushSceneTransitionEvent("free roam"));
    }

    void back() override { this->get_game()->quit(); };
};

class Player : public Object {
public:
    Player(Transform *parent, const arma::vec2 &position)
    :   Object(parent, position, false, 1.0)
    ,   _command_state({false, false, false, false})
    ,   _speed(1000.0)
    {

    }

    void up() { this->_command_state.move_up = true; }
    void left() { this->_command_state.move_left = true; }
    void down() { this->_command_state.move_down = true; }
    void right() { this->_command_state.move_right = true; }

    void update() override
    {
        arma::vec2 dir{0,0};
        if (this->_command_state.move_up)    dir[1] += 1.0;
        if (this->_command_state.move_down)  dir[1] -= 1.0;
        if (this->_command_state.move_left)  dir[0] -= 1.0;
        if (this->_command_state.move_right) dir[0] += 1.0;

        // this->set_velocity(dir*this->_speed);
        // or
        this->add_force(dir*this->_speed);

        arma::vec2 f = this->get_velocity();
        this->add_force(-f);

        this->_command_state = {false, false, false, false};

    }

private:
    struct {
        bool move_up;
        bool move_left;
        bool move_down;
        bool move_right;
    } _command_state;
    double _speed;
};

class DemoScene : public Scene {
public:
    explicit DemoScene(Game *game)
        : Scene(game, "free roam")
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
        o->set_colour(Colours::gray);
        o->set_renderable(MeshRenderable::regular_polygon(5));
        this->add_object(o);

        this->player = new Player(this, {30, 0});
        this->player->set_radius(4.0);
        this->player->set_colour(Colours::blue);
        this->player->set_renderable(new CircleRenderable());
        this->add_object(this->player);
        auto *cam = this->get_active_camera();
        cam->set_parent(this->player);

        this->fpscntr = new TextRenderable("FPS: ", DEFAULT_FONT, 100);
        this->fpscntr->set_alignment(HA_left, VA_bottom);
        this->fpscntr->set_position({1, 1});
        this->add_floating_renderable(this->fpscntr);
        this->fpscntr->set_parent(cam->get_bl());

        this->pos = new TextRenderable("<pos>", DEFAULT_FONT, 100);
        this->pos->set_alignment(HA_right, VA_bottom);
        this->pos->set_parent(cam->get_br());
        this->add_floating_renderable(this->pos);
    }

    void up() override { this->player->up(); }
    void left() override { this->player->left(); }
    void down() override { this->player->down(); }
    void right() override { this->player->right(); }

    void action() override {}
    void alternate() override {}

    void back() override { this->get_game()->add_event(new PopSceneTransitionEvent()); }

    void on_update() override
    {
        std::stringstream ss;
        ss << "FPS: " << Renderer::get().get_fps();
        std::string s = ss.str();
        this->fpscntr->set_text(s);

        auto p = this->player->get_position();
        auto v = this->player->get_velocity();
        ss.str("");
        ss << int(p[0]) << "." << int(p[1]) << ">>" << int(v[0]) << "." << int(v[1]);
        s = ss.str();
        this->pos->set_text(s);
    }

private:

    Player *player;
    TextRenderable *fpscntr, *pos;
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

class Boid : public Object {
public:
    explicit Boid(Scene *location, const arma::vec2 &position, double search_radius)
    : Object(location, position, false)
    , _loc(location)
    , _search_radius(search_radius)
    , _max_velocity(5.0)
    {
        double theta = M_2_PI * arma::randu();
        this->set_velocity( {this->_max_velocity*std::cos(theta), this->_max_velocity*std::sin(theta)} );
        this->set_renderable(new CircleRenderable());
        this->set_radius(0.5);
        this->set_layer("boids");
    }

    void update() override {
        std::vector<Object *> nearby = this->_loc->find_objects_near_to(this, this->_search_radius);
        if (nearby.empty())
            return;

        arma::vec2 f_sep, pos = this->get_position(), tot{0.0, 0.0};
        double n = 0.0;
        for (auto *obj : nearby) {
            if (obj == this)
                continue;
            if (obj->get_layer() != this->get_layer())
                continue;
            // separation - change direction to avoid collisions
            arma::vec2 dr = (obj->get_position() - pos);
            f_sep -= dr;
            tot += obj->get_velocity();
            n += 1.0;
        }
        this->set_force(f_sep);

        if (n >= 1.0) {
            // alignment - align velocity with nearby
            // cohesion - head for the centre of mass of boids
            arma::vec2 av = tot / n;
            //const double split = 0.9;
            //av = av*(1.0 - split) + this->get_velocity()*split;

            // av = av - 0.0001*this->get_position();
            //if (arma::norm(av) > this->_max_velocity)
            //    av  = this->_max_velocity*arma::normalise(av);
            this->set_velocity(av);
        }

        // bounds
        const double size = 100, hsize = size/2.;
        double x = pos[0], y = pos[1];
        if (x > hsize)  x -= size;
        if (x < -hsize) x += size;
        if (y > hsize)  y -= size;
        if (y < -hsize) y += size;
        this->set_position({x, y});
    }
private:
    Scene *_loc;
    double _search_radius, _max_velocity;
};


class BoidScene : public Scene {
public:

    explicit BoidScene(Game *game)
    : Scene(game, "sim")
    {
        const int n = 12;
        const double dtheta = M_PI * 2.0 / double(n);
        const double dr = 50.0 / double(n);
        double theta = 0.0;
        for (int j = 0; j < n; j++) {
            double r = dr;
            for (int i = 0; i < n; i++) {
                double x = r*std::cos(theta);
                double y = r*std::sin(theta);
                auto *boid = new Boid(this, {x, y}, 5.);
                this->add_object(boid);
                r += dr;
            }
            theta += dtheta;
        }

        this->observer = new Observer(this);

        auto *rct = MeshRenderable::rectangle(50, 50);
        rct->set_colour(Colour::from_grayscale(32));
        this->add_floating_renderable(rct);

        std::stringstream ss;
        ss << n*n << " objects";
        std::string s = ss.str();

        std::vector<std::string> lines = {
                s,
                "",
                "Behaviour rules:",
                " - Don't bump into each other",
                " - Align with each other",
        };
        constexpr double line_height = 10.0;
        double y = double(lines.size() - 1)*line_height/2.0;
        arma::vec2 origin{-150, y};
        for (const auto &line : lines) {
            if (line.empty()) {
                origin[1] -= line_height;
                continue;
            }
            auto *txt = new TextRenderable(line, DEFAULT_FONT, 80);
            txt->set_position(origin);
            txt->set_alignment(HA_left, VA_bottom);
            this->add_floating_renderable(txt);
            origin[1] -= line_height;
        }

        this->fpscntr = new TextRenderable("FPS: ", DEFAULT_FONT, 40);
        this->fpscntr->set_position({0, -60});
        this->add_floating_renderable(this->fpscntr);
        this->get_active_camera()->set_position({-50, 0});
    }

    void up() override { this->observer->add_force({0, 1e-3}); }
    void left() override { this->observer->add_force({-1e-3, 0}); }
    void down() override { this->observer->add_force({0, -1e-3}); }
    void right() override { this->observer->add_force({1e-3, 0}); }

    void action() override {}
    void alternate() override {}

    void back() override { this->get_game()->add_event(new PopSceneTransitionEvent()); }

    void on_update() override
    {
        std::wstringstream ss;
        ss << "FPS: " << Renderer::get().get_fps();
        std::wstring s = ss.str();
        this->fpscntr->set_text(s);
    }

private:

    Observer *observer;
    TextRenderable *fpscntr;

};

int main()
{
    std::cerr << GitMetadata::version_string() << std::endl;
    Game game(1280, 960);
    Renderer &r = Renderer::get();
    r.set_max_fps(100);
    r.define_shader("default", "vertex/vertex", "fragment/fragment");
    r.define_shader("sprite", "vertex/vertex", "fragment/sprite");
    r.define_shader("font", "vertex/vertex", "fragment/font");

    r.define_screen_effect_shader("default", "vertex/quad", "fragment/quad");
    Scene *scene = new DemoMenu(&game);
    game.add_scene(scene);
    scene = new DemoScene(&game);
    game.add_scene(scene);
    scene = new BoidScene(&game);
    game.add_scene(scene);
    game.run();
    return 0;
}
