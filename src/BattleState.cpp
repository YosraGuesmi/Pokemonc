#include "BattleState.hpp"
#include "ExplorationState.hpp"
#include "GameOverState.hpp"
#include <cstdlib> // Pour rand()
#include <ctime>   // Pour srand()
#include <iostream> // Ajout pour std::cout

BattleState::BattleState(PokemonAttack* playerTeam, Pokedex& dex)
    : playerTeam(playerTeam), pokedex(dex), playerIndex(0), playerTurn(true), battleActive(true) {
    srand(static_cast<unsigned>(time(nullptr)));
    playerPokemon = playerTeam->get(0);
    int enemyNum = rand() % pokedex.size() + 1;
    enemyPokemon = pokedex.clone(enemyNum);
    if (!playerPokemon) playerPokemon = playerTeam->get(0);


    playerHPBar.setSize(sf::Vector2f(200.f, 20.f));
    playerHPBar.setFillColor(sf::Color::Green);
    playerHPBar.setPosition(50.f, 50.f);

    enemyHPBar.setSize(sf::Vector2f(200.f, 20.f));
    enemyHPBar.setFillColor(sf::Color::Green);
    enemyHPBar.setPosition(550.f, 50.f);
}

BattleState::~BattleState() {
    delete enemyPokemon;
}

void BattleState::handleInput(GameContext& context, sf::Event event) {
    if (event.type == sf::Event::Closed) {
        context.getWindow().close();
    }
    if (!battleActive || !playerTurn) return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            int damage = (playerPokemon->getAttaque() * 0.8f) - (enemyPokemon->getDefense() * 0.5f);
            damage = std::max(1, damage);
            enemyPokemon->setPvActuel(enemyPokemon->getPvActuel() - damage);
            std::cout << "Joueur attaque ! Dégâts: " << damage << std::endl;
            playerTurn = false;
        } else if (event.key.code == sf::Keyboard::D) {
            std::cout << "Joueur se défend ! Réduction des dégâts prochains." << std::endl;
            playerTurn = false;
        } else if (event.key.code == sf::Keyboard::F) {
            if (rand() % 2 == 0) {
                std::cout << "Fuite réussie !" << std::endl;
                battleActive = false;
                context.setState(std::make_unique<ExplorationState>());
            } else {
                std::cout << "Fuite échouée !" << std::endl;
                playerTurn = false;
            }
        }
    }
}

void BattleState::update(GameContext& context) {
    if (!battleActive) return;

    if (!playerTurn) {

        int enemyAction = rand() % 2;
        int damage = (enemyPokemon->getAttaque() * (enemyAction == 1 ? 1.2f : 0.8f)) - (playerPokemon->getDefense() * 0.5f);
        damage = std::max(1, damage);
        playerPokemon->setPvActuel(playerPokemon->getPvActuel() - damage);
        std::cout << "Ennemi attaque ! Dégâts: " << damage << std::endl;

        if (playerPokemon->getPvActuel() <= 0) {
            delete playerPokemon;
            playerIndex++;
            if (playerIndex < static_cast<int>(playerTeam->size()) && playerTeam->get(playerIndex)) {
                playerPokemon = playerTeam->get(playerIndex);
                std::cout << "Pokémon suivant du joueur !" << std::endl;
            } else {
                std::cout << "Défaite ! Équipe KO." << std::endl;
                battleActive = false;
                context.setState(std::make_unique<GameOverState>());
                return;
            }
        }
        playerTurn = true;
    }


    float playerHPPercent = static_cast<float>(playerPokemon->getPvActuel()) / playerPokemon->getPvMax();
    playerHPBar.setSize(sf::Vector2f(200.f * playerHPPercent, 20.f));

    float enemyHPPercent = static_cast<float>(enemyPokemon->getPvActuel()) / enemyPokemon->getPvMax();
    enemyHPBar.setSize(sf::Vector2f(200.f * enemyHPPercent, 20.f));
}

void BattleState::render(GameContext& context, sf::RenderWindow& window) {
    if (!battleActive) return;

    window.clear(sf::Color::Black);

    if (playerPokemon && context.getLoadTexture()) {
        sf::Sprite playerSprite(context.getLoadTexture()(playerPokemon->getNumero()));
        playerSprite.setPosition(100.f, 200.f);
        playerSprite.setScale(2.f, 2.f);
        window.draw(playerSprite);
    }

    if (enemyPokemon && context.getLoadTexture()) {
        sf::Sprite enemySprite(context.getLoadTexture()(enemyPokemon->getNumero()));
        enemySprite.setPosition(500.f, 100.f);
        enemySprite.setScale(2.f, 2.f);
        window.draw(enemySprite);
    }


    window.draw(playerHPBar);
    window.draw(enemyHPBar);


    if (context.getFont()) {
        playerInfo.setFont(*context.getFont());
        enemyInfo.setFont(*context.getFont());
        actionText.setFont(*context.getFont());

        playerInfo.setString("PV: " + std::to_string(playerPokemon->getPvActuel()) + "/" + std::to_string(playerPokemon->getPvMax()));
        enemyInfo.setString("PV: " + std::to_string(enemyPokemon->getPvActuel()) + "/" + std::to_string(enemyPokemon->getPvMax()));
        playerInfo.setPosition(50.f, 80.f);
        enemyInfo.setPosition(550.f, 80.f);
        window.draw(playerInfo);
        window.draw(enemyInfo);

        if (playerTurn) {
            actionText.setString("Votre tour ! A: Attaquer, D: Défendre, F: Fuir");
        } else {
            actionText.setString("Tour de l'ennemi...");
        }
        actionText.setPosition(300.f, 500.f);
        window.draw(actionText);
    }

    window.display();
}