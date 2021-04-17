#pragma once

#include "../common/bounce.hpp"
#include "settings.hpp"
#include "boid.hpp"

class BoidScene final: public Scene {
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
                (void) boid;
                r += dr;
            }
            theta += dtheta;
        }

        auto *rct = MeshRenderable::rectangle(50, 50);
        rct->set_colour(Colour::from_grayscale(32));

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
            this->attach_renderable(txt);
            origin[1] -= line_height;
        }

        this->fpscntr = new TextRenderable("FPS: ", DEFAULT_FONT, 40);
        this->fpscntr->set_position({0, -60});
        this->attach_renderable(this->fpscntr);
        this->get_active_camera()->set_position({-50, 0});
    }

    void up() override {}
    void left() override {}
    void down() override {}
    void right() override {}

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

    TextRenderable *fpscntr;

};