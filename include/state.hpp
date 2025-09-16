#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include "GameContext.hpp"

class State {
public:
    virtual ~State() = default;
    virtual void handleInput(GameContext& context, sf::Event event) = 0;
    virtual void update(GameContext& context) = 0;
    virtual void render(GameContext& context, sf::RenderWindow& window) = 0; // Ajout de context
};

#endif