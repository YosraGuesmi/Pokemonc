#include "ExplorationState.hpp"
#include "RencontreState.hpp"
#include <cstdlib> // Pour rand()

void ExplorationState::handleInput(GameContext& context, sf::Event event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(context.getWindow());
    sf::Vector2f worldMousePos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (event.type == sf::Event::MouseButtonPressed && !*context.getIsDragging()) {
        if (mousePos.x < 400) {
            int adjustedY = static_cast<int>((mousePos.y + *context.getScrollOffset()) / 80);
            if (adjustedY >= 0 && static_cast<size_t>(adjustedY) < context.getParty()->size()) {
                *context.getDragIndex() = adjustedY;
                Pokemon* p = context.getParty()->remove(*context.getDragIndex());
                context.setDraggedPokemon(p);
                if (context.getDraggedPokemon()) {
                    *context.getIsDragging() = true;
                    *context.getDragOffset() = worldMousePos - sf::Vector2f(50.f + 64.f, 50.f + static_cast<float>(*context.getDragIndex() * 80) + 32.f);
                }
            }
        }
        if (rand() % 2 == 0) {
            context.setState(std::make_unique<RencontreState>());
        }
    } else if (event.type == sf::Event::MouseButtonReleased && *context.getIsDragging()) {
        *context.getIsDragging() = false;
        int releaseDropIndex = static_cast<int>(mousePos.y / 80);
        bool validDrop = false;
        if (mousePos.x < 400) {
            context.getParty()->add(context.getDraggedPokemon());
            validDrop = true;
        } else if (releaseDropIndex >= 0 && releaseDropIndex < 6 && context.getAttack()->size() < 6) {
            context.getAttack()->add(context.getDraggedPokemon());
            validDrop = true;
        }
        if (!validDrop) {
            if (*context.getDragIndex() >= 0 && *context.getDragIndex() < static_cast<int>(context.getParty()->size())) {
                context.getParty()->add(context.getDraggedPokemon());
            } else {
                context.getAttack()->add(context.getDraggedPokemon());
            }
        }
        delete context.getDraggedPokemon();
        context.setDraggedPokemon(nullptr);
        *context.getDragIndex() = -1;
    } else if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            *context.getScrollOffset() -= event.mouseWheelScroll.delta * context.getScrollSpeed();
            *context.getScrollOffset() = std::max(0.0f, std::min(*context.getScrollOffset(), std::max(0.0f, (context.getParty()->size() * 80.0f) - 600.0f)));
        }
    }
}

void ExplorationState::update(GameContext& context) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(context.getWindow());
    if (!*context.getIsDragging() && mousePos.x < 400 && context.getFont() && context.getTooltip()) {
        int adjustedY = static_cast<int>((mousePos.y + *context.getScrollOffset()) / 80);
        if (adjustedY >= 0 && static_cast<size_t>(adjustedY) < context.getParty()->size()) {
            auto p = context.getParty()->get(adjustedY);
            if (p) {
                context.getTooltip()->setString("Pokémon #" + std::to_string(p->getNumero()) + " (hover)");
                context.getTooltip()->setPosition(150.f, mousePos.y);
            } else {
                context.getTooltip()->setString("");
            }
        } else {
            context.getTooltip()->setString("");
        }
    }
}

void ExplorationState::render(GameContext& context, sf::RenderWindow& window) {
    window.clear(context.getBackgroundTexture() ? sf::Color::White : sf::Color(135, 206, 235));
    if (context.getBackgroundTexture() && context.getBackgroundTexture()->getSize().x > 0) {
        sf::Sprite backgroundSprite(*context.getBackgroundTexture());
        backgroundSprite.setScale(static_cast<float>(800) / context.getBackgroundTexture()->getSize().x, static_cast<float>(600) / context.getBackgroundTexture()->getSize().y);
        window.draw(backgroundSprite);
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    for (size_t i = 0; i < context.getParty()->size(); ++i) {
        auto p = context.getParty()->get(static_cast<int>(i));
        if (p) {
            sf::Sprite sprite(context.getLoadTexture()(p->getNumero()));
            float yPos = 50.f + static_cast<float>(i * 80) - *context.getScrollOffset();
            if (yPos >= -128.f && yPos <= 600.f) {
                sprite.setPosition(50.f, yPos);
                sprite.setScale(2.f, 2.f);
                window.draw(sprite);
            }
        }
    }

    for (int i = 0; i < 6; ++i) {
        sf::RectangleShape slot(sf::Vector2f(128.f, 64.f));
        slot.setPosition(400.f, 50.f + static_cast<float>(i * 80));
        auto slotP = context.getAttack()->get(i);
        slot.setFillColor(slotP ? sf::Color::Transparent : sf::Color(50, 50, 50, 100));
        slot.setOutlineColor(sf::Color::White);
        slot.setOutlineThickness(2.f);
        if (*context.getIsDragging() && mousePos.x >= 400 && *context.getDropIndex() == i && context.getAttack()->size() < 6) {
            slot.setFillColor(sf::Color(0, 255, 0, 100));
        }
        window.draw(slot);

        if (slotP) {
            sf::Sprite sprite(context.getLoadTexture()(slotP->getNumero()));
            sprite.setPosition(410.f, 55.f + static_cast<float>(i * 80));
            sprite.setScale(1.5f, 1.5f);
            window.draw(sprite);
        }
    }

    if (*context.getIsDragging() && context.getDraggedPokemon()) {
        sf::Sprite dragSprite(context.getLoadTexture()(context.getDraggedPokemon()->getNumero()));
        dragSprite.setPosition(worldMousePos - *context.getDragOffset());
        dragSprite.setScale(1.8f, 1.8f);
        dragSprite.setColor(sf::Color(255, 255, 255, 200));
        window.draw(dragSprite);
    }

    if (!*context.getIsDragging() && mousePos.x < 400 && context.getFont() && context.getTooltip()) {
        if (context.getTooltip()->getString() != "") {
            sf::RectangleShape tooltipBg(sf::Vector2f(context.getTooltip()->getLocalBounds().width + 10, context.getTooltip()->getLocalBounds().height + 5));
            tooltipBg.setPosition(150.f, mousePos.y);
            tooltipBg.setFillColor(sf::Color(0, 0, 0, 150));
            tooltipBg.setOutlineColor(sf::Color::White);
            tooltipBg.setOutlineThickness(1.f);
            window.draw(tooltipBg);
            window.draw(*context.getTooltip());
        }
    }
    window.display();
}