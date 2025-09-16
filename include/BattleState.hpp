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
    Pokemon* playerPokemon; // Pokémon actuel du joueur
    Pokemon* enemyPokemon;  // Pokémon ennemi
    int playerIndex;        // Index du Pokémon actuel dans l'équipe
    bool playerTurn;        // Tour du joueur ou de l'ennemi
    sf::RectangleShape playerHPBar, enemyHPBar; // Barres de PV
    sf::Text actionText;    // Texte pour les actions
    sf::Text playerInfo, enemyInfo; // Infos sur les PV
    bool battleActive;      // Indique si la bataille est en cours
};