#pragma once
#include <SFML/Graphics.hpp>
#include "../include/pokedex.hpp"
#include "../include/pokemon_party.hpp"
#include <vector>
#include <map>
#include <string>
#include <random>

class BattleSystem {
public:
    BattleSystem(std::vector<Pokemon*>& playerTeam, PokemonParty& opponentTeam, sf::Font& font);
    void processTurn(int playerAction, int attackIndex);
    void render(sf::RenderWindow& window, const std::map<int, sf::Texture>& textures);
    bool isBattleOver() const;
    std::string getBattleMessage() const { return battleMessage; }
    const std::vector<sf::Text>& getAttackButtons() const { return attackButtons; }

private:
    // Structure interne pour simuler une attaque
    struct Attack {
        std::string name;
        std::string type;
        int power;
        Attack(const std::string& n, const std::string& t, int p) : name(n), type(t), power(p) {}
    };

    // Équipes
    std::vector<Pokemon*> playerTeam;
    std::vector<Pokemon*> opponentTeam;
    Pokemon* activePlayerPokemon;
    Pokemon* activeOpponentPokemon;
    int currentPlayerIndex;
    int currentOpponentIndex;

    // Interface graphique
    sf::Font& font;
    sf::Text battleMessageText;
    std::vector<sf::Text> attackButtons;
    sf::RectangleShape playerHPBar;
    sf::RectangleShape opponentHPBar;
    sf::Text playerHPText;
    sf::Text opponentHPText;
    int selectedAttack;

    // Logique du combat
    std::string battleMessage;
    bool playerTurn;
    bool battleOver;

    // Table des types (simplifiée)
    std::map<std::string, std::map<std::string, float>> typeChart;
    void initializeTypeChart();
    float getTypeMultiplier(const std::string& attackType, const std::string& targetType);
    float calculateDamage(Pokemon* attacker, Pokemon* defender, const Attack& attack);
    void applyDamage(Pokemon* target, float damage);
    void selectOpponentAction(int& action, int& attackIndex);
};