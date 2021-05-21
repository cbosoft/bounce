#pragma once
#include <map>
#include <bounce/bounce.hpp>

#include "../player/player.hpp"

class Tile : public RectangleMeshRenderable {
public:
    explicit Tile(Transform *parent, const arma::vec2 &position)
    : RectangleMeshRenderable(10, 10)
    {
        this->set_colour(Colours::gray);
        this->set_border_colour(Colours::dark_gray);
        this->set_border_size(0.5);
        this->set_parent(parent);
        this->set_position(position);
        this->add_tag("tile");
    }
};

class TilePalette : public Transform {
public:
    TilePalette(Transform *parent)
    {

    }
};

class Collider : public Object {
public:
    Collider(Transform *parent, const arma::vec2 &position, const arma::vec2 &size)
    :   Object(parent)
    ,   p1(position)
    ,   additional_size(size)
    {
        this->set_p2(position);
        this->set_fixed(true);
        this->add_tag("collider");
    }

    void set_p2(const arma::vec2 &p2)
    {
        arma::vec2 avpos = (this->p1 + p2)*.5;
        this->set_position(avpos);

        arma::vec2 size = arma::abs(p2 - p1) + this->additional_size;
        this->set_shape(CollisionShape::rectangle(size[0], size[1]));
    }
private:
    arma::vec2 p1;
    arma::vec2 additional_size;
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
            std::list<Renderable *> tiles;
            this->target->find_in_children_cast("tile", tiles);
            for (auto *tile : tiles) {
                arma::vec2 ipos = arma::round(tile->get_position()/10.0);
                std::pair<int, int> i{ipos[0], ipos[1]};
                this->_tiles[i] = (Tile *)tile;
            }
            std::list<Object *> colliders;
            this->target->find_in_children_cast("collider", colliders);
            for (auto *collider : colliders) {
                this->add_collider_to_grid((Collider *)collider);
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
        Game::ref().show_colliders();
        this->player->set_fly_mode(true);
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

        if (this->placing_stuff) {
            this->place_stuff();
        }
        else if (this->removing_stuff) {
            this->remove_stuff();
        }
    }

    void start_placing_stuff()
    {
        this->placing_stuff = true;
        this->removing_stuff = false;
    }

    void stop_placing_stuff()
    {
        if (this->payload == PL_COLLIDER) {
            if (this->current_collider) {
                this->add_collider_to_grid(this->current_collider);
                this->current_collider = nullptr;
            }
        }
        this->placing_stuff = false;
        this->removing_stuff = false;
    }

    void add_collider_to_grid(Collider *collider)
    {
        arma::vec2 p = collider->get_position();
        double hw = collider->get_shape().w*.5;
        double hh = collider->get_shape().h*.5;

        auto left   = int((p[0] - hw)/this->grid_size);
        auto right  = int((p[0] + hw)/this->grid_size);
        auto top    = int((p[0] + hh)/this->grid_size);
        auto bottom = int((p[0] - hh)/this->grid_size);
        for (int xi = left; xi <= right; xi ++) {
            for (int yi = bottom; yi <= top; yi ++) {
                std::pair<int, int> pindex{xi, yi};
                this->_colliders[pindex] = collider;
            }
        }
    }

    void place_stuff()
    {
        arma::vec2 p = this->cursor->get_position();
        p = arma::round(p/this->grid_size);
        std::pair<int, int> pindex;
        pindex.first = int(p[0]);
        pindex.second = int(p[1]);
        p *= this->grid_size;
        switch (this->payload) {
            case PL_COLLIDER:
                this->place_collider(pindex, p);
                break;
            case PL_TILE:
                this->place_tile(pindex, p);
                break;
        }
    }

    void place_tile(const std::pair<int, int> &pindex, const arma::vec2 &p)
    {
        auto it = this->_tiles.find(pindex);
        if (it == this->_tiles.end()) {
            auto *tile = new Tile(this->target, p);
            this->_tiles[pindex] = tile;
        }
    }

    void place_collider(const std::pair<int, int> &pindex, const arma::vec2 &p)
    {
        (void) pindex;
        if (!this->current_collider) {
            this->current_collider = new Collider(this->target, p, {grid_size, grid_size});
        }
        this->current_collider->set_p2(p);
    }

    void start_removing_stuff() { this->removing_stuff = true; this->placing_stuff = false; }
    void stop_removing_stuff() { this->removing_stuff = false; this->placing_stuff = false; }
    void remove_stuff()
    {
        arma::vec2 p = this->cursor->get_position();
        p = arma::round(p/this->grid_size);
        std::pair<int, int> pindex;
        pindex.first = int(p[0]);
        pindex.second = int(p[1]);
        p *= this->grid_size;
        switch (this->payload) {
            case PL_COLLIDER:
                this->remove_collider(pindex, p);
                break;
            case PL_TILE:
                this->remove_tile(pindex, p);
                break;
        }
    }

    void remove_tile(const std::pair<int, int> &pindex, const arma::vec2 &p)
    {
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

    void remove_collider(const std::pair<int, int> &pindex, const arma::vec2 &p)
    {
        auto it = this->_colliders.find(pindex);
        if (it == this->_colliders.end()) {
            // do nothing
            std::cerr << "cannot remove collider; not found" << std::endl;
        }
        else {
            this->remove_collider(it->second);
        }
    }

    void remove_collider(Collider *collider)
    {
        arma::vec2 p = collider->get_position();
        double hw = collider->get_shape().w*.5;
        double hh = collider->get_shape().h*.5;

        auto left   = int((p[0] - hw)/this->grid_size);
        auto right  = int((p[0] + hw)/this->grid_size);
        auto top    = int((p[0] + hh)/this->grid_size);
        auto bottom = int((p[0] - hh)/this->grid_size);
        for (int xi = left; xi <= right; xi ++) {
            for (int yi = bottom; yi <= top; yi ++) {
                std::pair<int, int> pindex{xi, yi};
                auto it = this->_colliders.find(pindex);
                if (it != this->_colliders.end()) {
                    if (it->second == collider) {
                        this->_colliders.erase(it);
                    }
                }
            }
        }
        Game::ref().add_event(new TransformDestroyEvent(collider));
    }

    void left_pressed() override { this->player->left_pressed(); }
    void left_released() override { this->player->left_released(); }
    void right_pressed() override { this->player->right_pressed(); }
    void right_released() override { this->player->right_released(); }
    void up_pressed() override { this->player->up_pressed(); }
    void up_released() override { this->player->up_released(); }
    void down_pressed() override { this->player->down_pressed(); }
    void down_released() override { this->player->down_released(); }

    void action_pressed() override { this->start_placing_stuff(); }
    void action_released() override { this->stop_placing_stuff(); }
    void alternate_pressed() override { this->start_removing_stuff(); }
    void alternate_released() override { this->stop_removing_stuff(); }

    void key_char_pressed(char ch) override {
        switch (ch) {
            case 'q':
                this->player->toggle_fly_mode();
                break;

            case '1':
                this->payload = PL_TILE;
                break;

            case '2':
                this->payload = PL_COLLIDER;
                break;
        }
    }

private:
    Scene *target;
    arma::vec2 cursor_window_position;
    RectangleMeshRenderable *cursor;
    std::map<std::pair<int, int>, Tile *> _tiles;
    std::map<std::pair<int, int>, Collider *> _colliders;
    EditorPlayer *player;
    bool placing_stuff = false, removing_stuff = false;
    enum PAYLOAD { PL_TILE, PL_COLLIDER };
    PAYLOAD payload = PL_TILE;
    double grid_size = 10.;
    Collider *current_collider = nullptr;
};