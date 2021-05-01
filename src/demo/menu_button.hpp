#pragma once

#include <bounce/bounce.hpp>
#include "settings.hpp"

class DemoMenuButton final: public MenuItem
{
public:
    DemoMenuButton(Menu *parent, const std::string &label)
            : MenuItem(parent)
    {
        this->bg = new RectangleMeshRenderable(1, 1);
        this->bg->set_colour(Colours::black);
        this->attach_renderable("bg", this->bg);

        this->txt = new TextRenderable(label, DEFAULT_FONT, 80);
        this->bg->set_size(this->txt->measure() + 5.);
        this->attach_renderable("text", this->txt);

        //this->bg->set_border_size(0.01);
        this->bg->hide();
    }

    void highlight() override {
        //this->bg->set_colour(Colours::white);
        this->txt->set_colour(Colours::dark_gray);
    }

    void unhighlight() override {
        //this->bg->set_colour(Colours::black);
        this->txt->set_colour(Colours::white);
    }

    bool is_near(Transform *t, double thresh)
    {
        double dist = arma::norm(t->get_position() - this->get_position());
        return (dist < thresh);
    }

private:
    MeshRenderable *bg;
    TextRenderable *txt;

    friend class DemoMainMenu;
};
