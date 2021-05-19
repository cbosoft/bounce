#pragma once
#include <map>
#include <bounce/bounce.hpp>

#include "../menu_button.hpp"

class DemoKeyboardKey : public Tone, public MenuItem {
public:
    DemoKeyboardKey(Menu *owner, MusicNote note, int octave, const std::string &name, arma::vec2 position)
    :   Tone(note, octave)
    ,   MenuItem(owner)
    {
        rbl = new RectangleMeshRenderable(10, 10);
        rbl->set_parent(this);
        auto *txt = new TextRenderable(name, DEFAULT_FONT, 40);
        txt->set_colour(Colours::black);
        txt->set_parent(this);
        this->set_position(position);
    }

    void highlight() override
    {
        this->rbl->set_colour(Colours::white);
    }

    void unhighlight() override
    {
        this->rbl->set_colour(Colours::gray);
    }

    void play() override
    {
        this->highlight();
        Tone::play();
    }

    void pause() override
    {
        this->unhighlight();
        Tone::pause();
    }

private:
    RectangleMeshRenderable *rbl;
};

class DemoVolumeBar : public BarGraph {
public:
    DemoVolumeBar()
    : BarGraph(100, 10)
    {

    }

    [[nodiscard]] double measure_value() const override
    {
        return  SoundManager::ref().get_volume_mult();
    }

    [[nodiscard]] double measure_maximum() const override
    {
        return 1.0;
    }
};

class DemoMusicButton : public MenuItem {
public:
    DemoMusicButton(Menu *parent, const std::string &label, menu_callback cb)
    : MenuItem(parent)
    {
        this->bg = new RectangleMeshRenderable(1, 1);
        this->bg->set_colour(Colours::black);
        this->bg->set_parent(this);

        this->txt = new TextRenderable(label, DEFAULT_FONT, 80);
        this->txt->set_parent(this);
        this->bg->set_size(this->txt->measure() + 5.);

        this->set_callback_action(cb);
    }

    void highlight() override {
        this->bg->set_colour(Colours::white);
        this->txt->set_colour(Colours::black);
    }

    void unhighlight() override {
        this->bg->set_colour(Colours::clear);
        this->txt->set_colour(Colours::white);
    }
private:
    TextRenderable *txt;
    RectangleMeshRenderable *bg;
};


class DemoMusicEffectToggleButton : public MenuItem {
public:
    DemoMusicEffectToggleButton(Menu *parent, const std::string &label, menu_callback cb)
            : MenuItem(parent)
    {
        this->bg = new RectangleMeshRenderable(1, 1);
        this->bg->set_colour(Colours::black);
        this->bg->set_alignment(MR_HA_LEFT, MR_VA_CENTRE);
        this->bg->set_parent(this);

        this->txt = new TextRenderable(label, DEFAULT_FONT, 80);
        this->txt->set_alignment(HA_left, VA_centre);
        this->bg->set_size(this->txt->measure() + 5.);
        this->txt->set_parent(this);

        this->set_callback_action(cb);
    }

    void highlight() override {
        if (this->enabled) {
            this->bg->set_colour(Colours::blue);
        }
        else {
            this->bg->set_colour(Colours::light_gray);
        }
        this->txt->set_colour(Colours::black);
    }

    void unhighlight() override {
        this->bg->set_colour(Colours::clear);
        if (this->enabled) {
            this->txt->set_colour(Colours::blue);
        }
        else {
            this->txt->set_colour(Colours::light_gray);
        }
    }

    void action_pressed() override
    {
        this->enabled = !this->enabled;
        this->highlight();
        MenuItem::action_pressed();
    }

private:
    bool enabled = false;
    TextRenderable *txt;
    RectangleMeshRenderable *bg;
};

class DemoMusic final : public Menu {
public:
    DemoMusic()
            : Menu("demo music")
    {
        this->sounds['1'] = new DemoKeyboardKey(this, NOTE_A,       4, "A 4", {-85, 80});
        this->sounds['2'] = new DemoKeyboardKey(this, NOTE_A_SHARP, 4, "A#4", {-70, 80});
        this->sounds['3'] = new DemoKeyboardKey(this, NOTE_B,       4, "B 4", {-55, 80});
        this->sounds['4'] = new DemoKeyboardKey(this, NOTE_C,       4, "C 4", {-40, 80});
        this->sounds['5'] = new DemoKeyboardKey(this, NOTE_C_SHARP, 4, "C#4", {-25, 80});
        this->sounds['6'] = new DemoKeyboardKey(this, NOTE_D,       4, "D 4", {-10, 80});
        this->sounds['7'] = new DemoKeyboardKey(this, NOTE_D_SHARP, 4, "D#4", { 10, 80});
        this->sounds['8'] = new DemoKeyboardKey(this, NOTE_E,       4, "E 4", { 25, 80});
        this->sounds['9'] = new DemoKeyboardKey(this, NOTE_F,       4, "F 4", { 40, 80});
        this->sounds['0'] = new DemoKeyboardKey(this, NOTE_F_SHARP, 4, "F#4", { 55, 80});
        this->sounds['-'] = new DemoKeyboardKey(this, NOTE_G,       4, "G 4", { 70, 80});
        this->sounds['='] = new DemoKeyboardKey(this, NOTE_G_SHARP, 4, "G#4", { 85, 80});

        this->sounds['q'] = new DemoKeyboardKey(this, NOTE_A,       5, "A 5", {-85, 65});
        this->sounds['w'] = new DemoKeyboardKey(this, NOTE_A_SHARP, 5, "A#5", {-70, 65});
        this->sounds['e'] = new DemoKeyboardKey(this, NOTE_B,       5, "B 5", {-55, 65});
        this->sounds['r'] = new DemoKeyboardKey(this, NOTE_C,       5, "C 5", {-40, 65});
        this->sounds['t'] = new DemoKeyboardKey(this, NOTE_C_SHARP, 5, "C#5", {-25, 65});
        this->sounds['y'] = new DemoKeyboardKey(this, NOTE_D,       5, "D 5", {-10, 65});
        this->sounds['u'] = new DemoKeyboardKey(this, NOTE_D_SHARP, 5, "D#5", { 10, 65});
        this->sounds['i'] = new DemoKeyboardKey(this, NOTE_E,       5, "E 5", { 25, 65});
        this->sounds['o'] = new DemoKeyboardKey(this, NOTE_F,       5, "F 5", { 40, 65});
        this->sounds['p'] = new DemoKeyboardKey(this, NOTE_F_SHARP, 5, "F#5", { 55, 65});
        this->sounds['['] = new DemoKeyboardKey(this, NOTE_G,       5, "G 5", { 70, 65});
        this->sounds[']'] = new DemoKeyboardKey(this, NOTE_G_SHARP, 5, "G#5", { 85, 65});

        this->sounds['a']  = new DemoKeyboardKey(this, NOTE_A,       6, "A 6", {-85, 50});
        this->sounds['s']  = new DemoKeyboardKey(this, NOTE_A_SHARP, 6, "A#6", {-70, 50});
        this->sounds['d']  = new DemoKeyboardKey(this, NOTE_B,       6, "B 6", {-55, 50});
        this->sounds['f']  = new DemoKeyboardKey(this, NOTE_C,       6, "C 6", {-40, 50});
        this->sounds['g']  = new DemoKeyboardKey(this, NOTE_C_SHARP, 6, "C#6", {-25, 50});
        this->sounds['h']  = new DemoKeyboardKey(this, NOTE_D,       6, "D 6", {-10, 50});
        this->sounds['j']  = new DemoKeyboardKey(this, NOTE_D_SHARP, 6, "D#6", { 10, 50});
        this->sounds['k']  = new DemoKeyboardKey(this, NOTE_E,       6, "E 6", { 25, 50});
        this->sounds['l']  = new DemoKeyboardKey(this, NOTE_F,       6, "F 6", { 40, 50});
        this->sounds[';']  = new DemoKeyboardKey(this, NOTE_F_SHARP, 6, "F#6", { 55, 50});
        this->sounds['\''] = new DemoKeyboardKey(this, NOTE_G,       6, "G 6", { 70, 50});
        this->sounds['\\'] = new DemoKeyboardKey(this, NOTE_G_SHARP, 6, "G#6", { 85, 50});

        this->sounds['`'] = new DemoKeyboardKey(this, NOTE_A,       7, "A 7", {-85, 35});
        this->sounds['z'] = new DemoKeyboardKey(this, NOTE_A_SHARP, 7, "A#7", {-70, 35});
        this->sounds['x'] = new DemoKeyboardKey(this, NOTE_B,       7, "B 7", {-55, 35});
        this->sounds['c'] = new DemoKeyboardKey(this, NOTE_C,       7, "C 7", {-40, 35});
        this->sounds['v'] = new DemoKeyboardKey(this, NOTE_C_SHARP, 7, "C#7", {-25, 35});
        this->sounds['b'] = new DemoKeyboardKey(this, NOTE_D,       7, "D 7", {-10, 35});
        this->sounds['n'] = new DemoKeyboardKey(this, NOTE_D_SHARP, 7, "D#7", { 10, 35});
        this->sounds['m'] = new DemoKeyboardKey(this, NOTE_E,       7, "E 7", { 25, 35});
        this->sounds[','] = new DemoKeyboardKey(this, NOTE_F,       7, "F 7", { 40, 35});
        this->sounds['.'] = new DemoKeyboardKey(this, NOTE_F_SHARP, 7, "F#7", { 55, 35});
        this->sounds['/'] = new DemoKeyboardKey(this, NOTE_G,       7, "G 7", { 70, 35});
        //this->sounds[''] = new Tone(NOTE_G_SHARP, 7);

        for (auto kv: this->sounds)
            kv.second->unhighlight();

        auto *note = new TextRenderable("Mash the keys!", DEFAULT_FONT, 100);
        note->set_parent(this);
        note->set_position({0, 10});

        auto *note3 = new TextRenderable("<esc> to go back to the menu", DEFAULT_FONT, 70);
        note3->set_parent(this);
        note3->set_position({0, -10});

        this->clip = new ClipAfterEffect();
        this->chorus = new ChorusAfterEffect(0.1f);
        this->bitcrush = new BitCrushAfterEffect(0.2f);
        // this->clip->enable();

        this->cursor = new RegularPolygonMeshRenderable(20);
        this->cursor->set_parent(this);


        { // volume bar
            auto *volbar = new DemoVolumeBar();
            volbar->set_parent(this);
            volbar->set_position({-50, -20});
            //volbar->set_angle(M_PI_2);

            auto *volup = new DemoMusicButton(this, "+", DemoMusic::volume_up_cb);
            this->add_item(volup);
            volup->set_position({60, -20});

            auto *voldown = new DemoMusicButton(this, "-", DemoMusic::volume_down_cb);
            this->add_item(voldown);
            voldown->set_position({-60, -20});
        }

        {
            auto *btn = new DemoMusicEffectToggleButton(this, "toggle clip", DemoMusic::toggle_clip_cb);
            this->add_item(btn);
            btn->set_position({-50, -40});
        }
        {
            auto *btn = new DemoMusicEffectToggleButton(this, "toggle bit crush", DemoMusic::toggle_bitcrush_cb);
            this->add_item(btn);
            btn->set_position({-50, -60});
        }
        {
            auto *btn = new DemoMusicEffectToggleButton(this, "toggle chorus", DemoMusic::toggle_chorus_cb);
            this->add_item(btn);
            btn->set_position({-50, -80});
        }
    }

    static void volume_up_cb(MenuItem *i)
    {
        (void) i;
        float vol = SoundManager::ref().get_volume_mult();
        SoundManager::ref().set_volume_mult(vol + 0.1f);
    }

    static void volume_down_cb(MenuItem *i)
    {
        (void) i;
        float vol = SoundManager::ref().get_volume_mult();
        SoundManager::ref().set_volume_mult(vol - 0.1f);
    }

    static void toggle_clip_cb(MenuItem *i)
    {
        auto *music_menu = (DemoMusic *)i->get_parent_menu();
        music_menu->toggle_clip();
    }

    void toggle_clip()
    {
        this->clip->toggle();
    }

    static void toggle_bitcrush_cb(MenuItem *i)
    {
        auto *music_menu = (DemoMusic *)i->get_parent_menu();
        music_menu->toggle_bitcrush();
    }

    void toggle_bitcrush()
    {
        this->bitcrush->toggle();
    }

    static void toggle_chorus_cb(MenuItem *i)
    {
        auto *music_menu = (DemoMusic *)i->get_parent_menu();
        music_menu->toggle_chorus();
    }

    void toggle_chorus()
    {
        this->chorus->toggle();
    }

    void cursor_position(const arma::vec2 &p) override
    {
        this->cursor_window_position = p;
    }

    void key_char_pressed(char c) override
    {
        auto it = this->sounds.find(c);
        if (it != this->sounds.end())
            it->second->play();

        if (c == '#') this->clip->enable();
    }

    void key_char_released(char c) override
    {
        auto it = this->sounds.find(c);
        if (it != this->sounds.end())
            it->second->pause();

        if (c == '#') this->clip->disable();
    }

    void back_pressed() override
    {
        Game::ref().add_event(new PopSceneTransitionEvent());
    }

    void on_activate() override
    {
        Renderer::get().set_screen_effect("default");
    }

    void on_update() override
    {
        this->position_cursor();
    }

    void position_cursor()
    {
        arma::vec2 wrld = Renderer::get().screen_pos_to_world_pos(this->cursor_window_position);
        this->cursor->set_position(wrld);

        this->set_selected(nullptr);
        for (auto *item : this->get_items()) {
            double d = arma::norm(item->get_position() - wrld);
            if (d < 5.0) {
                this->set_selected(item);
            }
        }
    }

private:
    std::map<char, DemoKeyboardKey *> sounds;
    SoundAfterEffect *clip, *bitcrush, *chorus;
    arma::vec2 cursor_window_position;
    RegularPolygonMeshRenderable *cursor;
};