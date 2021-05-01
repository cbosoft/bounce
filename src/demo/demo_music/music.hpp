#pragma once
#include <map>
#include <bounce/bounce.hpp>

class DemoMusic final : public Scene {
public:
    DemoMusic()
    : Scene("demo music")
    {
        this->sounds['1'] = new Tone(105);
        this->sounds['q'] = new Tone(155);
        this->sounds['a'] = new Tone(205);
        this->sounds['z'] = new Tone(255);

        this->sounds['2'] = new Tone(305);
        this->sounds['w'] = new Tone(355);
        this->sounds['s'] = new Tone(405);
        this->sounds['x'] = new Tone(455);

        this->sounds['3'] = new Tone(505);
        this->sounds['e'] = new Tone(555);
        this->sounds['d'] = new Tone(605);
        this->sounds['c'] = new Tone(655);

        this->sounds['4'] = new Tone(705);
        this->sounds['r'] = new Tone(755);
        this->sounds['f'] = new Tone(805);
        this->sounds['v'] = new Tone(855);

        this->sounds['5'] =  new Tone(905);
        this->sounds['t'] =  new Tone(955);
        this->sounds['g'] = new Tone(1005);
        this->sounds['b'] = new Tone(1055);

        this->sounds['6'] = new Tone(1105);
        this->sounds['y'] = new Tone(1155);
        this->sounds['h'] = new Tone(1205);
        this->sounds['n'] = new Tone(1255);

        this->sounds['7'] = new Tone(1305);
        this->sounds['u'] = new Tone(1355);
        this->sounds['j'] = new Tone(1405);
        this->sounds['m'] = new Tone(1455);

        this->sounds['8'] = new Tone(1505);
        this->sounds['i'] = new Tone(1555);
        this->sounds['k'] = new Tone(1505);
        this->sounds[','] = new Tone(1555);

        this->sounds['9'] = new Tone(1605);
        this->sounds['o'] = new Tone(1655);
        this->sounds['l'] = new Tone(1705);
        this->sounds['.'] = new Tone(1755);

        this->sounds['0'] = new Tone(1805);
        this->sounds['p'] = new Tone(1855);
        this->sounds[';'] = new Tone(1905);
        this->sounds['/'] = new Tone(1955);

        auto *note = new TextRenderable("Mash the keys!", DEFAULT_FONT, 100);
        this->attach_renderable(note);
        note->set_position({0, 10});

        auto *note3 = new TextRenderable("<esc> to go back to the menu", DEFAULT_FONT, 70);
        this->attach_renderable(note3);
        note3->set_position({0, -10});
    }

    void key_char_pressed(char c) override
    {
        auto it = this->sounds.find(c);
        if (it != this->sounds.end())
            it->second->play();
    }

    void key_char_released(char c) override
    {
        auto it = this->sounds.find(c);
        if (it != this->sounds.end())
            it->second->pause();
    }

    void back_pressed() override
    {
        Game::ref().add_event(new PopSceneTransitionEvent());
    }

    void on_activate() override
    {
        Renderer::get().set_screen_effect("default");
    }

private:
    std::map<char, Sound *> sounds;
};