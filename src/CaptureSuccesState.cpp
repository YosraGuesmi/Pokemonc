#include "CaptureSuccesState.hpp"
#include "ExplorationState.hpp"

void CaptureSuccesState::handleInput(GameContext& context, sf::Event event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        context.setState(std::make_unique<ExplorationState>());
    }
}

void CaptureSuccesState::update(GameContext& context) {
    // Logique de mise à jour si nécessaire
}

void CaptureSuccesState::render(GameContext& context, sf::RenderWindow& window) {
    window.clear(sf::Color::Yellow); // Couleur d'exemple
    if (context.getFont() && context.getMainText()) {
        window.draw(*context.getMainText());
    }
    window.display();
}