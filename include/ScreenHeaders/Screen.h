//
// Created by User on 6/7/2025.
//

#ifndef SCREEN_H
#define SCREEN_H
#include "raylib.h"

enum class ScreenType {
    NONE,
    BATTLE,
    LOAD_SAVED,
};

class Screen {
protected:
    const int screenX = 1920;
    const int screenY = 1180;
    Font font{};
    Music music{};
    Texture2D background{};
public:
    virtual void init() = 0;
    virtual ScreenType update() = 0;
    virtual void draw() = 0;
    virtual void cleanup() = 0;
    virtual ~Screen() = default;
};

#endif //SCREEN_H
