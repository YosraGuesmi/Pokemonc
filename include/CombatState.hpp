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
    Pokemon* playerPokemon; // Pokémon actuel du joueur
    Pokemon* enemyPokemon; // Pokémon ennemi
    int playerIndex = 0; // Index du Pokémon actuel dans l'équipe
    bool playerTurn = true; // Tour du joueur ou de l'ennemi
    sf::RectangleShape playerHPBar, enemyHPBar; // Barres de PV
    sf::Text actionText; // Texte pour les actions
};

#endif