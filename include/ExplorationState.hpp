#ifndef EXPLORATIONSTATE_HPP
#define EXPLORATIONSTATE_HPP

#include "State.hpp"

class ExplorationState : public State {
public:
    virtual void handleInput(GameContext& context, sf::Event event) override;
    virtual void update(GameContext& context) override;
    virtual void render(GameContext& context, sf::RenderWindow& window) override;
};

#endif