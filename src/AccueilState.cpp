#include "AccueilState.hpp"
#include "ExplorationState.hpp"


void AccueilState::handleInput(GameContext& context, sf::Event event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        context.setState(std::make_unique<ExplorationState>());
    }
}

void AccueilState::update(GameContext& context) {

}

void AccueilState::render(GameContext& context, sf::RenderWindow& window) {
    window.clear(sf::Color::Blue);
    if (context.getFont() && context.getMainText()) {
        window.draw(*context.getMainText());
    }
    window.display();
}