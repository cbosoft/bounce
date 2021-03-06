#pragma once
#include <bounce/bounce.hpp>
#include "settings.hpp"
#include "menu_button.hpp"

class MenuCursor final: public AnimatedMeshRenderable {
public:
    explicit MenuCursor(Transform *parent)
            : AnimatedMeshRenderable(new RegularPolygonMeshRenderable(3))
    {
        this->set_parent(parent);
        this->set_z(-100);
        this->_original_size = {2, 2};
    }
};

// class MenuAnimLogo final : public RectangleMeshRenderable {
// public:
//     explicit MenuAnimLogo(Transform *parent)
//         :   RectangleMeshRenderable(48, 8)
//         ,   _speed(10)
//         ,   _countdown(_speed)
//     {
//         this->set_parent(parent);
//         this->set_z(-100);
//         this->set_texture_name("anim-test-logo");
//         this->_current_texture_loop = this->_texture->get_named_loop("loop");
//         this->set_angle(M_PI_2);
//     }
//
//     void on_update() override
//     {
//         if (!this->_countdown--) {
//             TextureFrameCoords tc = this->_texture->get_texcoords_of_frame(this->_current_frame);
//             this->_current_frame++;
//             if (this->_current_frame > this->_current_texture_loop.to) {
//                 this->_current_frame = this->_current_texture_loop.from;
//             }
//             this->_countdown = this->_speed;
//         }
//     }
//
// private:
//     int _speed, _countdown;
// };

class DemoMainMenu final: public Menu {
public:
    explicit DemoMainMenu()
            :   Menu("menu")
    {
        this->icon = new AnimatedBounceIcon();
        this->icon->set_parent(this);
        this->icon->set_position({0, 35});

        auto *txt = new TextRenderable("Bounce Demo Collection", DEFAULT_FONT, 150);
        txt->set_colour(Colour::from_rgb(240, 240, 220));
        txt->set_position({0, 60});
        txt->set_parent(this);

        {
            auto *b = new DemoMenuButton(this, "space shooter (pew pew)");
            b->set_position({0, 10});
            this->add_item(b);
            b->set_callback_action(DemoMainMenu::free_roam_callback);
        }
        {
            auto *b = new DemoMenuButton(this, "platformer (jump around)");
            b->set_position({0, -5});
            this->add_item(b);
            b->set_callback_action(DemoMainMenu::platformer_cb);
        }
        {
            auto *b = new DemoMenuButton(this, "music (doo bee doo)");
            b->set_position({0, -20});
            this->add_item(b);
            b->set_callback_action(DemoMainMenu::music_cb);
        }
        {
            auto *b = new DemoMenuButton(this, "demo #4");
            b->set_position({0, -35});
            this->add_item(b);
            // TODO b->set_callback_action(DemoMainMenu::/* callback */);
        }
        {
            auto *b = new DemoMenuButton(this, "quit");
            b->set_position({0, -55});
            this->add_item(b);
            b->set_callback_action(DemoMainMenu::quit_callback);
        }

        this->cursor = new MenuCursor(this);
        this->cursor->set_position({10, 0});

        std::string tag = TextManager::ref().get_collection("tagline")->get_string("tagline");
        tag += " ";
        auto *tagline = new TextRenderable(tag, DEFAULT_FONT, 50);
        tagline->set_alignment(HA_right, VA_centre);
        tagline->set_colour(Colour::from_grayscale(127));
        tagline->set_position({0, -75});
        tagline->set_parent(this);
        auto *tagline2 = new TextRenderable("BounceEngine", DEFAULT_FONT, 80);
        tagline2->set_alignment(HA_left, VA_centre);
        tagline2->set_colour(Colour::from_grayscale(200));
        tagline2->set_position({0, -75});
        tagline2->set_parent(this);

        auto *bg = new RectangleMeshRenderable(500, 300);
        bg->set_parent(this);
        bg->set_colour(Colour::from_grayscale(50));
        bg->set_z(-1000);

        const int w = 2048, h = w, c = 4;
        auto *data = new unsigned char[w*h*c];
        for (int xi = 0; xi < w; xi++) {
            for (int yi = 0; yi < h; yi++) {
                double x = xi*.01;
                double y = yi*.01;

                double noise = (Perlin::noise3d(x, y, 0.0)+1.)*.5;
                auto alpha = uint8_t(noise*255);

                //noise = (Perlin::noise3d(x, y, 1.0)+.5);
                //auto hue = uint8_t(noise*255);

                data[xi*h*c + yi*c + 0] = 255;
                data[xi*h*c + yi*c + 1] = 255;
                data[xi*h*c + yi*c + 2] = 255;
                data[xi*h*c + yi*c + 3] = alpha;
            }
        }
        auto *t = new Texture("noise1");
        t->set_image_data(data, w, h);
        Renderer::get().add_texture(t);
    }

    static void quit_callback(MenuItem *i)
    {
        Game::ref().quit();
    }

    static void free_roam_callback(MenuItem *i)
    {
        Game::ref().add_event(new PushSceneTransitionEvent("demo space shooter"));
    }

    static void platformer_cb(MenuItem *i)
    {
        Game::ref().add_event(new PushSceneTransitionEvent("demo platformer"));
    }

    static void music_cb(MenuItem *i)
    {
        Game::ref().add_event(new PushSceneTransitionEvent("demo music"));
    }

    void cursor_position(const arma::vec2 &p) override
    {
        arma::vec2 wrld = Renderer::get().screen_pos_to_world_pos(p);
        this->cursor->set_position(wrld);
    }

    void check_select_buttons()
    {
        for (MenuItem *item : this->get_items()) {
            auto *btn = (DemoMenuButton *)item;
            if (btn->is_near(this->cursor, 5.0)) {
                this->cursor->animate_to(btn->bg, 10);
                this->cursor->set_position(btn->get_position());
                this->set_selected(btn);
                return;
            }
        }
        this->cursor->animate_to_original(5);
        this->set_selected(nullptr);
    }

    void on_update() override
    {
        check_select_buttons();
    }

    void back_pressed() override { Game::ref().quit(); };

private:
    MenuCursor *cursor;
    MeshRenderable *icon;
};
