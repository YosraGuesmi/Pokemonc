#include "RencontreState.hpp"
#include "CaptureSuccesState.hpp"

void RencontreState::handleInput(GameContext& context, sf::Event event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        context.setState(std::make_unique<CaptureSuccesState>());
    }
}

void RencontreState::update(GameContext& context) {
    // Logique de mise à jour si nécessaire
}

void RencontreState::render(GameContext& context, sf::RenderWindow& window) {
    window.clear(sf::Color::Green); // Couleur d'exemple
    if (context.getFont() && context.getMainText()) {
        window.draw(*context.getMainText());
    }
    window.display();
}