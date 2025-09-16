#include "GameOverState.hpp"

void GameOverState::handleInput(GameContext& context, sf::Event event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        context.setState(nullptr); // Retour au menu principal ou fermeture, à ajuster
    }
}

void GameOverState::update(GameContext& context) {
    // Logique de mise à jour si nécessaire
}

void GameOverState::render(GameContext& context, sf::RenderWindow& window) {
    window.clear(sf::Color::Black); // Fond noir pour "Game Over"
    if (context.getFont() && context.getMainText()) {
        context.getMainText()->setString("Game Over\nPress Escape to exit");
        context.getMainText()->setPosition(300.f, 250.f);
        window.draw(*context.getMainText());
    }
    window.display();
}