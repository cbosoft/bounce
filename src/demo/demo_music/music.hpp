#pragma once
#include <map>
#include <bounce/bounce.hpp>

class DemoMusic final : public Scene {
public:
    DemoMusic()
    : Scene("demo music")
    {
        this->sounds['1'] = new Tone(NOTE_A,       4);
        this->sounds['2'] = new Tone(NOTE_A_SHARP, 4);
        this->sounds['3'] = new Tone(NOTE_B,       4);
        this->sounds['4'] = new Tone(NOTE_C,       4);
        this->sounds['5'] = new Tone(NOTE_C_SHARP, 4);
        this->sounds['6'] = new Tone(NOTE_D,       4);
        this->sounds['7'] = new Tone(NOTE_D_SHARP, 4);
        this->sounds['8'] = new Tone(NOTE_E,       4);
        this->sounds['9'] = new Tone(NOTE_F,       4);
        this->sounds['0'] = new Tone(NOTE_F_SHARP, 4);
        this->sounds['-'] = new Tone(NOTE_G,       4);
        this->sounds['='] = new Tone(NOTE_G_SHARP, 4);

        this->sounds['q'] = new Tone(NOTE_A,       5);
        this->sounds['w'] = new Tone(NOTE_A_SHARP, 5);
        this->sounds['e'] = new Tone(NOTE_B,       5);
        this->sounds['r'] = new Tone(NOTE_C,       5);
        this->sounds['t'] = new Tone(NOTE_C_SHARP, 5);
        this->sounds['y'] = new Tone(NOTE_D,       5);
        this->sounds['u'] = new Tone(NOTE_D_SHARP, 5);
        this->sounds['i'] = new Tone(NOTE_E,       5);
        this->sounds['o'] = new Tone(NOTE_F,       5);
        this->sounds['p'] = new Tone(NOTE_F_SHARP, 5);
        this->sounds['['] = new Tone(NOTE_G,       5);
        this->sounds[']'] = new Tone(NOTE_G_SHARP, 5);

        this->sounds['a'] = new Tone(NOTE_A,       6);
        this->sounds['s'] = new Tone(NOTE_A_SHARP, 6);
        this->sounds['d'] = new Tone(NOTE_B,       6);
        this->sounds['f'] = new Tone(NOTE_C,       6);
        this->sounds['g'] = new Tone(NOTE_C_SHARP, 6);
        this->sounds['h'] = new Tone(NOTE_D,       6);
        this->sounds['j'] = new Tone(NOTE_D_SHARP, 6);
        this->sounds['k'] = new Tone(NOTE_E,       6);
        this->sounds['l'] = new Tone(NOTE_F,       6);
        this->sounds[';'] = new Tone(NOTE_F_SHARP, 6);
        this->sounds['\''] = new Tone(NOTE_G,       6);
        this->sounds['\\'] = new Tone(NOTE_G_SHARP, 6);

        this->sounds['`'] = new Tone(NOTE_A,       7);
        this->sounds['z'] = new Tone(NOTE_A_SHARP, 7);
        this->sounds['x'] = new Tone(NOTE_B,       7);
        this->sounds['c'] = new Tone(NOTE_C,       7);
        this->sounds['v'] = new Tone(NOTE_C_SHARP, 7);
        this->sounds['b'] = new Tone(NOTE_D,       7);
        this->sounds['n'] = new Tone(NOTE_D_SHARP, 7);
        this->sounds['m'] = new Tone(NOTE_E,       7);
        this->sounds[','] = new Tone(NOTE_F,       7);
        this->sounds['.'] = new Tone(NOTE_F_SHARP, 7);
        this->sounds['/'] = new Tone(NOTE_G,       7);
        //this->sounds[''] = new Tone(NOTE_G_SHARP, 7);

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