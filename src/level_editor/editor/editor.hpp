#pragma once
#include <map>
#include <bounce/bounce.hpp>

#include "../player/player.hpp"

class Tile : public Object {
public:
    explicit Tile(Transform *parent, const arma::vec2 &position)
    :   Object(parent)
    {
        auto *bg = new RectangleMeshRenderable(10, 10);
        bg->set_colour(Colours::gray);
        bg->set_border_colour(Colours::dark_gray);
        bg->set_border_size(0.5);
        bg->set_parent(this);
        this->set_shape(CollisionShape::rectangle(10, 10));
        this->set_fixed(true);
        this->set_position(position);
    }
};

class TilePalette : public Transform {
public:
    TilePalette(Transform *parent)
    {

    }
};

class LevelEditor final : public Scene {
public:
    LevelEditor()
    : Scene("level editor")
    {
        this->cursor = new RectangleMeshRenderable(10, 10);
        this->cursor->set_colour(Colour::from_rgb(255, 255, 0, 127));
        this->cursor->set_z(100);
        this->cursor->set_parent(this);

        this->player = new EditorPlayer(this);
        this->player->set_position({0, 30});

        auto *gravity = new GravityField(200);
        this->add_field(gravity);
        auto *airres = new AirResField(0.7);
        this->add_field(airres);

        this->get_active_camera()->set_parent(this->player);

        try {
            json j = ResourceManager::ref().get_metadata("scene", "test");
            this->target = (Scene *)Game::ref().deserialise(j);
            std::list<Object *> objs;
            this->target->find_in_children_cast("object", objs);
            for (auto *obj : objs) {
                arma::vec2 ipos = arma::round(obj->get_position()/10.0);
                std::pair<int, int> i{ipos[0], ipos[1]};
                this->_tiles[i] = (Tile *)obj;
            }
        }
        catch (const std::runtime_error &e) {
            this->target = new Scene("test");
            auto *tile = new Tile(this->target, {0, 0});
            this->_tiles[std::pair<int, int>(0, 0)] = tile;
        }
        this->target->set_parent(this);
    }

    void on_activate() override
    {
        //PhysicsEngine::ref().set_timescale(4.0);
    }

    void back_pressed() override
    {
        json j = this->target->serialise();
        std::string json_str = j.dump(2);
        std::ofstream of("../resources/scene/test.json");
        of << json_str;
        Game::ref().quit();
    }

    void cursor_position(const arma::vec2 &p) override
    {
        this->cursor_window_position = p;
    }
    void on_update() override
    {
        this->position_cursor();
    }

    void position_cursor()
    {
        arma::vec2 wrld = Renderer::get().screen_pos_to_world_pos(this->cursor_window_position);
        const double tile_size = 10.;
        wrld = arma::round(wrld/tile_size)*tile_size;
        this->cursor->set_position(wrld);

        if (this->placing_tiles) {
            this->place_tile();
        }
        else if (this->removing_tiles) {
            this->remove_tile();
        }
    }

    void place_tile()
    {
        arma::vec2 p = this->cursor->get_position();
        const double tile_size = 10.;
        p /= tile_size;
        p = arma::round(p);
        std::pair<int, int> pindex;
        pindex.first = int(p[0]);
        pindex.second = int(p[1]);
        auto it = this->_tiles.find(pindex);
        if (it == this->_tiles.end()) {
            auto *tile = new Tile(this->target, p * tile_size);
            this->_tiles[pindex] = tile;
        }
    }

    void remove_tile()
    {
        arma::vec2 p = this->cursor->get_position();
        const double tile_size = 10.;
        p /= tile_size;
        p = arma::round(p);
        std::pair<int, int> pindex;
        pindex.first = int(p[0]);
        pindex.second = int(p[1]);
        auto it = this->_tiles.find(pindex);
        if (it == this->_tiles.end()) {
            // do nothing
        }
        else {
            auto *tile = it->second;
            this->_tiles.erase(it);
            Game::ref().add_event(new TransformDestroyEvent(tile));
        }
    }

    void left_pressed() override { this->player->left_pressed(); }
    void left_released() override { this->player->left_released(); }
    void right_pressed() override { this->player->right_pressed(); }
    void right_released() override { this->player->right_released(); }
    void up_pressed() override { this->player->up_pressed(); }
    void up_released() override { this->player->up_released(); }
    void down_pressed() override { this->player->down_pressed(); }
    void down_released() override { this->player->down_released(); }

    void action_pressed() override { this->placing_tiles = true; this->removing_tiles = false; }
    void action_released() override { this->placing_tiles = false; this->removing_tiles = false; }
    void alternate_pressed() override { this->placing_tiles = false; this->removing_tiles = true; }
    void alternate_released() override { this->placing_tiles = false; this->removing_tiles = false; }

    void key_char_pressed(char ch) override {
        if (ch == 'q')
            this->player->toggle_fly_mode();
    }

private:
    Scene *target;
    arma::vec2 cursor_window_position;
    RectangleMeshRenderable *cursor;
    std::map<std::pair<int, int>, Tile *> _tiles;
    EditorPlayer *player;
    bool placing_tiles = false, removing_tiles = false;
};