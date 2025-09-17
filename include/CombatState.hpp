#ifndef COMBATSTATE_HPP
#define COMBATSTATE_HPP

#include "State.hpp"
#include "../include/pokedex.hpp"
#include <SFML/Graphics.hpp>

class CombatState : public State {
public:
    CombatState(PokemonAttack* playerTeam, Pokedex& dex);
    virtual void handleInput(GameContext& context, sf::Event event) override;
    virtual void update(GameContext& context) override;
    virtual void render(GameContext& context, sf::RenderWindow& window) override;

private:
    PokemonAttack* playerTeam;
    Pokedex& pokedex;
    Pokemon* playerPokemon;
    Pokemon* enemyPokemon;
    int playerIndex = 0;
    bool playerTurn = true;
    sf::RectangleShape playerHPBar, enemyHPBar;
    sf::Text actionText;

#endif