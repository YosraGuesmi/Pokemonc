#include "BattleSystem.hpp"
#include <iostream>
#include <algorithm>

BattleSystem::BattleSystem(std::vector<Pokemon*>& playerTeam, PokemonParty& opponentTeam, sf::Font& font)
    : playerTeam(playerTeam), font(font), selectedAttack(-1), playerTurn(true), battleOver(false) {

    for (int i = 0; i < 6; ++i) {
        if (auto p = opponentTeam.get(i)) {
            this->opponentTeam.push_back(p);
        }
    }
    activePlayerPokemon = playerTeam[0];
    activeOpponentPokemon = opponentTeam.get(0);
    currentPlayerIndex = 0;
    currentOpponentIndex = 0;


    initializeTypeChart();


    battleMessageText.setFont(font);
    battleMessageText.setCharacterSize(20);
    battleMessageText.setFillColor(sf::Color::White);
    battleMessageText.setOutlineColor(sf::Color::Black);
    battleMessageText.setOutlineThickness(1.0f);
    battleMessageText.setPosition(20.f, 500.f);

    std::vector<std::string> dummyAttacks = {"Attaque1", "Attaque2", "Attaque3", "Attaque4"};
    for (size_t i = 0; i < dummyAttacks.size(); ++i) {
        sf::Text button;
        button.setFont(font);
        button.setCharacterSize(20);
        button.setFillColor(sf::Color::White);
        button.setOutlineColor(sf::Color::Black);
        button.setOutlineThickness(1.0f);
        button.setString(dummyAttacks[i]);
        button.setPosition(20.f + i * 200.f, 450.f);
        attackButtons.push_back(button);
    }

    playerHPBar.setSize(sf::Vector2f(200.f, 20.f));
    playerHPBar.setFillColor(sf::Color::Green);
    playerHPBar.setPosition(20.f, 300.f);
    opponentHPBar.setSize(sf::Vector2f(200.f, 20.f));
    opponentHPBar.setFillColor(sf::Color::Green);
    opponentHPBar.setPosition(580.f, 50.f);

    playerHPText.setFont(font);
    playerHPText.setCharacterSize(16);
    playerHPText.setFillColor(sf::Color::White);
    playerHPText.setPosition(20.f, 275.f);

    opponentHPText.setFont(font);
    opponentHPText.setCharacterSize(16);
    opponentHPText.setFillColor(sf::Color::White);
    opponentHPText.setPosition(580.f, 25.f);

    battleMessage = "Choisissez une attaque !";
}

void BattleSystem::initializeTypeChart() {

    typeChart["Feu"]["Plante"] = 2.0f;
    typeChart["Feu"]["Eau"] = 0.5f;
    typeChart["Eau"]["Feu"] = 2.0f;
    typeChart["Eau"]["Plante"] = 0.5f;
    typeChart["Plante"]["Eau"] = 2.0f;
    typeChart["Plante"]["Feu"] = 0.5f;
}

float BattleSystem::getTypeMultiplier(const std::string& attackType, const std::string& targetType) {
    float multiplier = 1.0f;
    if (typeChart[attackType].find(targetType) != typeChart[attackType].end()) {
        multiplier = typeChart[attackType][targetType];
    }
    return multiplier;
}

float BattleSystem::calculateDamage(Pokemon* attacker, Pokemon* defender, const Attack& attack) {

    float baseDamage = ((2 * 50 / 5 + 2) * attack.power * attacker->getAttaque() / defender->getDefense()) / 50 + 2;

    std::string defenderType = "Normal";
    float typeMultiplier = getTypeMultiplier(attack.type, defenderType);
    float randomFactor = (std::rand() % 16 + 85) / 100.0f;
    return baseDamage * typeMultiplier * randomFactor;
}

void BattleSystem::applyDamage(Pokemon* target, float damage) {
    int newHP = std::max(0, static_cast<int>(target->getPvActuel() - damage));
    target->setPvActuel(newHP);
    if (newHP <= 0) {
        battleMessage = target == activePlayerPokemon ? "Votre Pokémon est K.O. !" : "Le Pokémon adverse est K.O. !";
        if (target == activePlayerPokemon) {
            currentPlayerIndex++;
            if (currentPlayerIndex < playerTeam.size()) {
                activePlayerPokemon = playerTeam[currentPlayerIndex];
                battleMessage += " Vous envoyez un nouveau Pokémon !";
            } else {
                battleOver = true;
                battleMessage = "Vous avez perdu le combat !";
            }
        } else {
            currentOpponentIndex++;
            if (currentOpponentIndex < opponentTeam.size()) {
                activeOpponentPokemon = opponentTeam[currentOpponentIndex];
                battleMessage += " L'adversaire envoie un nouveau Pokémon !";
            } else {
                battleOver = true;
                battleMessage = "Vous avez gagné le combat !";
            }
        }
    }
}

void BattleSystem::selectOpponentAction(int& action, int& attackIndex) {
    action = 0;
    attackIndex = std::rand() % 4;
}

void BattleSystem::processTurn(int playerAction, int attackIndex) {
    if (battleOver || !playerTurn) return;

    battleMessage = "";
    int opponentAction, opponentAttackIndex;
    selectOpponentAction(opponentAction, opponentAttackIndex);

    Attack dummyAttack("Attaque" + std::to_string(attackIndex + 1), "Feu", 50);
    Attack dummyOpponentAttack("Attaque" + std::to_string(opponentAttackIndex + 1), "Eau", 50);


    bool playerFirst = true;

    auto executeAction = [&](Pokemon* attacker, Pokemon* defender, int action, int attackIdx, const Attack& attack) {
        if (action == 0 && attackIdx >= 0 && attackIdx < 4) {
            float damage = calculateDamage(attacker, defender, attack);
            applyDamage(defender, damage);
            battleMessage += attacker == activePlayerPokemon ? "Votre " : "Le ";
            battleMessage += "Pokemon utilise " + attack.name + " ! ";
            std::string defenderType = "Normal";
            float typeMultiplier = getTypeMultiplier(attack.type, defenderType);
            if (typeMultiplier > 1.0f) battleMessage += "C'est super efficace ! ";
            else if (typeMultiplier < 1.0f && typeMultiplier > 0.0f) battleMessage += "Ce n'est pas très efficace... ";
            else if (typeMultiplier == 0.0f) battleMessage += "Cela n'a aucun effet ! ";
        }
    };

    if (playerFirst) {
        executeAction(activePlayerPokemon, activeOpponentPokemon, playerAction, attackIndex, dummyAttack);
        if (!battleOver) executeAction(activeOpponentPokemon, activePlayerPokemon, opponentAction, opponentAttackIndex, dummyOpponentAttack);
    } else {
        executeAction(activeOpponentPokemon, activePlayerPokemon, opponentAction, opponentAttackIndex, dummyOpponentAttack);
        if (!battleOver) executeAction(activePlayerPokemon, activeOpponentPokemon, playerAction, attackIndex, dummyAttack);
    }

    playerTurn = true;
}

void BattleSystem::render(sf::RenderWindow& window, const std::map<int, sf::Texture>& textures) {

    if (activePlayerPokemon) {
        sf::Sprite playerSprite(textures.at(activePlayerPokemon->getNumero()));
        playerSprite.setPosition(50.f, 350.f);
        playerSprite.setScale(1.5f, 1.5f);
        window.draw(playerSprite);
    }
    if (activeOpponentPokemon) {
        sf::Sprite opponentSprite(textures.at(activeOpponentPokemon->getNumero()));
        opponentSprite.setPosition(600.f, 100.f);
        opponentSprite.setScale(1.5f, 1.5f);
        window.draw(opponentSprite);
    }


    if (activePlayerPokemon) {
        float hpRatio = static_cast<float>(activePlayerPokemon->getPvActuel()) / activePlayerPokemon->getPvMax();
        playerHPBar.setSize(sf::Vector2f(200.f * hpRatio, 20.f));
        playerHPBar.setFillColor(hpRatio > 0.5f ? sf::Color::Green : hpRatio > 0.2f ? sf::Color::Yellow : sf::Color::Red);
        playerHPText.setString("PV: " + std::to_string(activePlayerPokemon->getPvActuel()) + "/" + std::to_string(activePlayerPokemon->getPvMax()));
        window.draw(playerHPBar);
        window.draw(playerHPText);
    }
    if (activeOpponentPokemon) {
        float hpRatio = static_cast<float>(activeOpponentPokemon->getPvActuel()) / activeOpponentPokemon->getPvMax();
        opponentHPBar.setSize(sf::Vector2f(200.f * hpRatio, 20.f));
        opponentHPBar.setFillColor(hpRatio > 0.5f ? sf::Color::Green : hpRatio > 0.2f ? sf::Color::Yellow : sf::Color::Red);
        opponentHPText.setString("PV: " + std::to_string(activeOpponentPokemon->getPvActuel()) + "/" + std::to_string(activeOpponentPokemon->getPvMax()));
        window.draw(opponentHPBar);
        window.draw(opponentHPText);
    }


    for (size_t i = 0; i < attackButtons.size(); ++i) {
        if (static_cast<int>(i) == selectedAttack) {
            attackButtons[i].setFillColor(sf::Color::Yellow);
        } else {
            attackButtons[i].setFillColor(sf::Color::White);
        }
        window.draw(attackButtons[i]);
    }


    battleMessageText.setString(battleMessage);
    window.draw(battleMessageText);
}

bool BattleSystem::isBattleOver() const {
    return battleOver;
}