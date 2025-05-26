//
// Created by User on 5/25/2025.
//

#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H
#include "raylib.h"

class WelcomeScreen {

private:

    const int screenX = 736;
    const int screenY = 920;

protected:

    Music screenMusic{};
    Texture2D screenTexture{};

public:
    // these functions will likely be inherited (and overridden) for BattleWindow and WinnerWindow later on.
    void init_music();
    void init_window(); // textures and the window itself.
    void clear_music() const;
    void clear_window() const;
    void while_window_open();
    void draw_button();
    void when_button_clicked();
    void clear_button();
};
#endif //WELCOMESCREEN_H
