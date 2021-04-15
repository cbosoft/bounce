#pragma once

#include "../common/bounce.hpp"
#include "settings.hpp"

class MenuButton final: public MenuItem
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
