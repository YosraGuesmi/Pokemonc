#include "GameOverState.hpp"

void GameOverState::handleInput(GameContext& context, sf::Event event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        context.setState(nullptr);
    }
}

void GameOverState::update(GameContext& context) {

}

void GameOverState::render(GameContext& context, sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    if (context.getFont() && context.getMainText()) {
        context.getMainText()->setString("Game Over\nPress Escape to exit");
        context.getMainText()->setPosition(300.f, 250.f);
        window.draw(*context.getMainText());
    }
    window.display();
}