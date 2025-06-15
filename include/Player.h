#ifndef PLAYER_H
#define PLAYER_H

#include "Dynamic_array.h"
#include "String.h"
#include "Pokemon.h"

class GameContext;
class Action;

class Player {
private:
    Dynamic_array<Pokemon*> team;
    Pokemon* activePokemon;
    bool pokedexUsed;
    int altarCharges;
    bool hasExtraTurn = false;


public:
    Player(const Dynamic_array<Pokemon*>& initialTeam);
    ~Player();

    Dynamic_array<Pokemon*>& getTeam() { return team; }
    Pokemon* getActivePokemon() const { return activePokemon; }
    bool hasAvailablePokemon() const;
    void switchPokemon(int index);

    bool hasUsedPokedex() const { return pokedexUsed; }
    void setUsedPokedex(bool used) { pokedexUsed = used; }

    int getAltarCharges() const { return altarCharges; }
    void gainAltarCharge(int count = 1) { altarCharges += count; }
    void useAltarCharge() { if (altarCharges > 0) --altarCharges; }
    void grantExtraTurn() {
        hasExtraTurn = true;
    }
    Action* chooseAction(GameContext& context);

    void onPokemonFainted();
};

#endif // PLAYER_H