#pragma once

#include "../common/bounce.hpp"
#include "settings.hpp"

class MenuButton final: public MenuItem
{
public:
    MenuButton(Menu *parent, const std::string &label)
            : MenuItem(parent)
    {
        this->bg = MeshRenderable::rectangle(30, 5);
        this->bg->set_colour(Colours::black);
        this->attach_renderable("bg", this->bg);

        this->txt = new TextRenderable(label, DEFAULT_FONT, 80);
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

    friend class MainMenu;
};
