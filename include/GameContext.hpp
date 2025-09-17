#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include <functional>
#include "../include/pokemon_party.hpp"
#include "../include/pokemon_attack.hpp"
#include <map>

// Déclaration forward de State
class State;

class GameContext {
public:
    GameContext(int width, int height);
    void setState(std::unique_ptr<State> state);
    std::unique_ptr<State> getState() { return std::move(currentState); }
    void handleEvents();
    void update();
    void render();
    bool isWindowOpen() const;
    sf::RenderWindow& getWindow();


    void setParty(PokemonParty* p) { party = p; }
    void setAttack(PokemonAttack* a) { attack = a; }
    void setTextures(std::map<int, sf::Texture>* t) { textures = t; }
    void setLoadTexture(std::function<sf::Texture&(int)>& lt) { loadTexture = lt; }
    void setFont(sf::Font* f) { font = f; }
    void setBackgroundTexture(sf::Texture* bt) { backgroundTexture = bt; }
    void setMainText(sf::Text* mt) { mainText = mt; }
    void setTooltip(sf::Text* t) { tooltip = t; }
    void setGlassTextLayers(std::vector<sf::Text>* gtl) { glassTextLayers = gtl; }

    PokemonParty* getParty() { return party; }
    PokemonAttack* getAttack() { return attack; }
    std::map<int, sf::Texture>* getTextures() { return textures; }
    std::function<sf::Texture&(int)>& getLoadTexture() { return loadTexture; }
    sf::Font* getFont() { return font; }
    sf::Texture* getBackgroundTexture() { return backgroundTexture; }
    sf::Text* getMainText() { return mainText; }
    sf::Text* getTooltip() { return tooltip; }
    std::vector<sf::Text>* getGlassTextLayers() { return glassTextLayers; }


    int* getDragIndex() { return &dragIndex; }
    void setDraggedPokemon(Pokemon* p) { draggedPokemon = p; }
    Pokemon* getDraggedPokemon() { return draggedPokemon; }
    bool* getIsDragging() { return &isDragging; }
    sf::Vector2f* getDragOffset() { return &dragOffset; }
    float* getScrollOffset() { return &scrollOffset; }
    float getScrollSpeed() { return scrollSpeed; }
    void setDropIndex(int* di) { dropIndex = di; }
    int* getDropIndex() { return dropIndex; }

private:
    std::unique_ptr<State> currentState;
    sf::RenderWindow window;
    PokemonParty* party = nullptr;
    PokemonAttack* attack = nullptr;
    std::map<int, sf::Texture>* textures = nullptr;
    std::function<sf::Texture&(int)> loadTexture;
    sf::Font* font = nullptr;
    sf::Texture* backgroundTexture = nullptr;
    sf::Text* mainText = nullptr;
    sf::Text* tooltip = nullptr;
    std::vector<sf::Text>* glassTextLayers = nullptr;

    int dragIndex = -1;
    Pokemon* draggedPokemon = nullptr;
    bool isDragging = false;
    sf::Vector2f dragOffset = sf::Vector2f(0.f, 0.f);
    float scrollOffset = 0.f;
    float scrollSpeed = 10.f;
    int* dropIndex = nullptr;
};

#endif