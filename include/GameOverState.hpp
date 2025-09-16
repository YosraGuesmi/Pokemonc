#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "State.hpp"

class GameOverState : public State {
public:
    virtual void handleInput(GameContext& context, sf::Event event) override;
    virtual void update(GameContext& context) override;
    virtual void render(GameContext& context, sf::RenderWindow& window) override; // Correction ici
};

#endif