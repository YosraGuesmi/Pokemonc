#ifndef ACCUEILSTATE_HPP
#define ACCUEILSTATE_HPP

#include "State.hpp"

class AccueilState : public State {
public:
    virtual void handleInput(GameContext& context, sf::Event event) override;
    virtual void update(GameContext& context) override;
    virtual void render(GameContext& context, sf::RenderWindow& window) override;
};

#endif