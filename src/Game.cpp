#include "Game.h"
#include "Action.h"
#include "UltraNecrozma.h"
#include <fstream>

Game::Game(Player* p1, Player* p2)
    : player1(p1), player2(p2), currentPlayer(p1), opponentPlayer(p2),
      logger("docs/log.txt"), context(nullptr),
      extraActionGranted(false), shieldedPokemon(nullptr), shieldFactor(0.0f) {}

Game::~Game() {
    delete context;
}

void Game::start() {
    Dynamic_array<Pokemon*> pool;
    pool.push(new UltraNecrozma());  // will add more later
    pool.push(new UltraNecrozma());  // placeholder

    assignRandomTeams(pool);

    currentPlayer->switchPokemon(0);
    opponentPlayer->switchPokemon(0);

    context = new GameContext(this, currentPlayer, opponentPlayer,
                              currentPlayer->getActivePokemon(),
                              opponentPlayer->getActivePokemon(),
                              &logger);

    currentPlayer->getActivePokemon()->playTheme();
    currentPlayer->getActivePokemon()->onEntry(*context);
    context->getAttacker()->playTheme();  // Player 1 goes first
}

void Game::assignRandomTeams(const Dynamic_array<Pokemon*>& pool) {
    // Simplified for now: first 2 go to p1, next 2 to p2
    Dynamic_array<Pokemon*> team1;
    Dynamic_array<Pokemon*> team2;
    for (int i = 0; i < pool.size(); ++i) {
        if (i % 2 == 0) team1.push(pool[i]);
        else team2.push(pool[i]);
    }

    player1->getTeam().clear();
    for (int i = 0; i < team1.size(); ++i) {
        player1->getTeam().push(team1[i]);
    }

    player2->getTeam().clear();
    for (int i = 0; i < team1.size(); ++i) {
        player2->getTeam().push(team1[i]);
    }

}

void Game::runTurn() {
    Action* action = currentPlayer->chooseAction(*context);
    processAction(action);
    delete action;

    if (!extraActionGranted)
        switchPlayers();
    else
        extraActionGranted = false;
}

void Game::processAction(Action* action) {
    context->getLogger().logEvent("Action begins.");
    action->execute(*context);
    context->getLogger().logEvent("Action ends.");
}

void Game::switchPlayers() {
    Player* temp = currentPlayer;
    currentPlayer = opponentPlayer;
    opponentPlayer = temp;

    delete context;
    context = new GameContext(this, currentPlayer, opponentPlayer,
                              currentPlayer->getActivePokemon(),
                              opponentPlayer->getActivePokemon(),
                              &logger);
}

bool Game::isGameOver() const {
    return !player1->hasAvailablePokemon() || !player2->hasAvailablePokemon();
}

Player* Game::getWinner() const {
    if (player1->hasAvailablePokemon()) return player1;
    if (player2->hasAvailablePokemon()) return player2;
    return nullptr;
}

void Game::grantExtraAction() {
    extraActionGranted = true;
}

void Game::shieldNextDamage(Pokemon* p, float factor) {
    shieldedPokemon = p;
    shieldFactor = factor;
}

void Game::saveToFile(const string& filepath) const {
    std::ofstream out(filepath.c_str(), std::ios::binary);
    if (!out) return;

    int p1HP = player1->getActivePokemon()->getCurrentHP();
    out.write((char*)&p1HP, sizeof(int));
    // will add more details.
    out.close();
}

void Game::loadFromFile(const string& filepath) {
    std::ifstream in(filepath.c_str(), std::ios::binary);
    if (!in) return;

    int hp = 0;
    in.read((char*)&hp, sizeof(int));
    player1->getActivePokemon()->takeDamage(player1->getActivePokemon()->getCurrentHP() - hp);
    in.close();
}