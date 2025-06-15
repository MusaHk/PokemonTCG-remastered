#include "Player.h"
#include "ActionHeaders/AttackAction.h"

Player::Player(const Dynamic_array<Pokemon*>& initialTeam)
    : team(initialTeam), activePokemon(nullptr),
      pokedexUsed(false), altarCharges(0)
{
    if (team.size() > 0) {
        activePokemon = team[0];
    }
}

Player::~Player() = default;

bool Player::hasAvailablePokemon() const {
    for (int i = 0; i < team.size(); ++i) {
        if (!team[i]->isFainted()) return true;
    }
    return false;
}

void Player::switchPokemon(int index) {
    if (index >= 0 && index < team.size() && !team[index]->isFainted()) {
        activePokemon = team[index];
    }
    activePokemon->playTheme();
}

Action* Player::chooseAction(GameContext& context) {
    // Temporary stub: always attack with move 0
    return new AttackAction(0);
}

void Player::onPokemonFainted() {
    for (int i = 0; i < team.size(); ++i) {
        if (!team[i]->isFainted()) {
            activePokemon = team[i];
            break;
        }
    }
}