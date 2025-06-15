#ifndef POKEMON_H
#define POKEMON_H

#include "Dynamic_array.h"
#include "String.h"
#include "raylib.h"
#include "GameContext.h"

class Player;

class Pokemon {
protected:
    string name;
    int maxHP;
    int currentHP;
    int maxEnergy;
    int currentEnergy;
    bool isEX;
    Texture2D frontSprite;
    Texture2D backSprite;
    Music themeMusic;

public:
    Pokemon(const string& name, int maxHP, int maxEnergy, bool isEX, const char* frontSpritePath, const char* backSpritePath,
            const char* musicPath)
        : name(name), maxHP(maxHP), currentHP(maxHP), maxEnergy(maxEnergy), currentEnergy(0), isEX(isEX)
    {
        frontSprite = LoadTexture(frontSpritePath);
        backSprite = LoadTexture(backSpritePath);
        themeMusic = LoadMusicStream(musicPath);
    }

    virtual ~Pokemon() {
        UnloadTexture(frontSprite);
        UnloadTexture(backSprite);
        UnloadMusicStream(themeMusic);
    }

    // Core attributes
    string getName() const { return name; }
    int getCurrentHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getCurrentEnergy() const { return currentEnergy; }
    int getMaxEnergy() const { return maxEnergy; }
    bool getIsEX() const { return isEX; }

    bool isFainted() const {
        return currentHP <= 0;
    }
    void takeDamage(int amount) {
        currentHP = currentHP > amount ? currentHP - amount : 0;
    }
    void heal(int amount) {
        currentHP = (currentHP + amount < maxHP) ? currentHP + amount : maxHP;
    }
    void gainEnergy(int amount) {
        currentEnergy = (currentEnergy + amount < maxEnergy) ? currentEnergy + amount : maxEnergy;
    }
    void useEnergy(int amount) {
        currentEnergy = currentEnergy > amount ? currentEnergy - amount : 0;
    }

    // Sprites & music
    Texture2D getFrontSprite() const { return frontSprite; }
    Texture2D getBackSprite() const { return backSprite; }
    void playTheme() {
        StopMusicStream(themeMusic);
        PlayMusicStream(themeMusic);
    }
    Music& getThemeMusic() { return themeMusic; }

    virtual void onEntry(GameContext& ctx) = 0;
    virtual void onExit(GameContext& ctx) {}

    virtual void applyPassive(GameContext& ctx) = 0;
    virtual void applyMove(int moveIndex, GameContext& ctx) = 0;

    // UI data
    virtual Dynamic_array<string> getMoveNames() const = 0;
    virtual string getMoveDescription(int moveIndex) const = 0;
    virtual int getMoveCost(int moveIndex) const = 0;
    virtual bool canUseMove(int moveIndex) const {
        return currentEnergy >= getMoveCost(moveIndex);
    }

    virtual string getPassiveName() const = 0;
    virtual string getPassiveDescription() const = 0;
};

#endif // POKEMON_H