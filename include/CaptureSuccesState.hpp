#ifndef CAPTURESUCCESSTATE_HPP
#define CAPTURESUCCESSTATE_HPP

#include "State.hpp"

class CaptureSuccesState : public State {
public:
    virtual void handleInput(GameContext& context, sf::Event event) override;
    virtual void update(GameContext& context) override;
    virtual void render(GameContext& context, sf::RenderWindow& window) override;
};

#endif