#include "BattleScreen.h"
#include <cstdio>  // for std::sprintf

static const char* BACK_FMT  = "assets/sprites/back/%sBack.gif";
static const char* FRONT_FMT = "assets/sprites/front/%sFront.gif";

BattleScreen::BattleScreen(Game* game)
    : game(game),
      background{}, music{}, font{},
      gifImageP1{}, gifTexP1{}, gifFramesP1(0),
      currentFrameP1(0), frameTimerP1(0), frameDelayP1(1/12.0f),
      gifImageP2{}, gifTexP2{}, gifFramesP2(0),
      currentFrameP2(0), frameTimerP2(0), frameDelayP2(1/12.0f)
{}

void BattleScreen::init() {
    background = LoadTexture("assets/images/BattleScreenClouds.jpg");
    font = LoadFont("assets/fonts/Extrude-90aK.ttf");

    game->start();

    char path1[256], path2[256];
    {
        const string& name1 = game->getContext()
                                 .getCurrentPlayer()
                                 ->getActivePokemon()
                                 ->getName();
        const string& name2 = game->getContext()
                                 .getOpponent()
                                 ->getActivePokemon()
                                 ->getName();
        std::sprintf(path1, BACK_FMT,  name1.c_str());
        std::sprintf(path2, FRONT_FMT, name2.c_str());
    }

    gifImageP1 = LoadImageAnim(path1, &gifFramesP1);
    gifTexP1 = LoadTextureFromImage(gifImageP1);
    currentFrameP1 = 0;
    frameTimerP1 = 0.0f;

    gifImageP2 = LoadImageAnim(path2, &gifFramesP2);
    gifTexP2 = LoadTextureFromImage(gifImageP2);
    currentFrameP2 = 0;
    frameTimerP2 = 0.0f;
}

ScreenType BattleScreen::update() {
    if (Pokemon* active = game->getContext().getAttacker()) {
        UpdateMusicStream(active->getThemeMusic());
    }

    float dt = GetFrameTime();

    frameTimerP1 += dt;
    if (frameTimerP1 >= frameDelayP1) {
        frameTimerP1 -= frameDelayP1;
        currentFrameP1 = (currentFrameP1 + 1) % gifFramesP1;
        size_t offsetP1 = gifImageP1.width * gifImageP1.height * 4 * currentFrameP1;
        UpdateTexture(gifTexP1, static_cast<unsigned char *>(gifImageP1.data) + offsetP1);
    }

    frameTimerP2 += dt;
    if (frameTimerP2 >= frameDelayP2) {
        frameTimerP2 -= frameDelayP2;
        currentFrameP2 = (currentFrameP2 + 1) % gifFramesP2;
        size_t offsetP2 = gifImageP2.width * gifImageP2.height * 4 * currentFrameP2;
        UpdateTexture(gifTexP2, static_cast<unsigned char *>(gifImageP2.data) + offsetP2);
    }

    game->runTurn();

    if (game->isGameOver()) {
        return ScreenType::LOAD_SAVED;  // Placeholder until ScreenType::WINNER ready.
    }
    return ScreenType::NONE;
}

void BattleScreen::draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(background, 0, 0, WHITE);
    DrawTextureEx(gifTexP1, {200.0f, 750.0f}, 0.0f, 3.5f, WHITE);
    DrawTextureEx(gifTexP2, {1150.0f, 150.0f}, 0.0f, 3.5f, WHITE);

    EndDrawing();
}

void BattleScreen::cleanup() {
    StopMusicStream(music);
    UnloadMusicStream(music);
    UnloadFont(font);
    UnloadTexture(background);
    UnloadTexture(gifTexP1);
    UnloadImage(gifImageP1);
    UnloadTexture(gifTexP2);
    UnloadImage(gifImageP2);
    delete game;
}