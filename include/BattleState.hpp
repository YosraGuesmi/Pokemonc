#pragma once
#include "State.hpp"
#include "pokedex.hpp"
#include "pokemon_attack.hpp"
#include <SFML/Graphics.hpp>

class BattleState : public State {
public:
    BattleState(PokemonAttack* playerTeam, Pokedex& dex);
    virtual ~BattleState();
    virtual void handleInput(GameContext& context, sf::Event event) override;
    virtual void update(GameContext& context) override;
    virtual void render(GameContext& context, sf::RenderWindow& window) override;

private:
    PokemonAttack* playerTeam;
    Pokedex& pokedex;
    Pokemon* playerPokemon;
    Pokemon* enemyPokemon;
    int playerIndex;
    bool playerTurn;
    sf::RectangleShape playerHPBar, enemyHPBar;
    sf::Text actionText;
    sf::Text playerInfo, enemyInfo;
    bool battleActive;
};