#include "GameContext.hpp"
#include "State.hpp"

GameContext::GameContext(int width, int height) : window(sf::VideoMode(width, height), "Pokemon Project") {

}

void GameContext::setState(std::unique_ptr<State> state) {
    currentState = std::move(state);
}

void GameContext::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (currentState) currentState->handleInput(*this, event);
        if (event.type == sf::Event::Closed) window.close();
    }
}

void GameContext::update() {
    if (currentState) currentState->update(*this);
}

void GameContext::render() {
    if (currentState) currentState->render(*this, window);
    window.display();
}

bool GameContext::isWindowOpen() const {
    return window.isOpen();
}

sf::RenderWindow& GameContext::getWindow() {
    return window;
}