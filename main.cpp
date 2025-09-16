#include "../pokemon/PokemonStorage/Pokedex.hpp"
#include "../pokemon/PokemonBat/PokemonParty.hpp"
#include "../pokemon/PokemonBat/PokemonAttack.hpp"
#include <iostream>
#include <vector>
<<<<<<< HEAD

int main() {
    try {
        Pokedex& pokedex = Pokedex::get_instance();
        PokemonParty party;
        Pokemon* bulbasaur = pokedex.clone_pokemon(1);
        Pokemon* charmander = pokedex.clone_pokemon(4);
        if (bulbasaur && charmander) {
            party.add_pokemon(*bulbasaur);
            party.add_pokemon(*charmander);
            delete bulbasaur;
            delete charmander;
        } else {
            std::cerr << "Error: Unable to clone Pokemon from Pokedex.\n";
            return 1;
        }

        std::cout << "PokemonParty size: " << party.size() << "\n";
        for (size_t i = 0; i < party.size(); ++i) {
            const Pokemon* p = party.get_pokemon(i);
            if (p) {
                std::cout << "Pokemon " << i << ": " << p->get_name()
                          << ", HP: " << p->get_current_hp() << "/" << p->get_max_hp()
                          << ", Attack: " << p->get_attack()
                          << ", Defense: " << p->get_defense() << "\n";
            }
        }

        std::vector<int> indices = {0, 1};
        PokemonAttack attack_team(party, indices);

        const Pokemon* p1_const = attack_team.get_pokemon(0);
        const Pokemon* p2_const = attack_team.get_pokemon(1);
        if (p1_const && p2_const) {
            Pokemon p1(*p1_const);
            Pokemon p2(*p2_const);
            std::cout << "\n" << p1.get_name() << " attacks " << p2.get_name() << "!\n";
            int damage = p1.attack(p2);
            std::cout << p2.get_name() << " takes " << damage << " damage, HP now: "
                      << p2.get_current_hp() << "/" << p2.get_max_hp() << "\n";
        } else {
            std::cerr << "Error: Unable to retrieve Pokemon for attack.\n";
            return 1;
        }

        attack_team.reintegrate_to_party(party);
        std::cout << "\nPokemonParty size after reintegration: " << party.size() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
=======
#include <cmath>
#include <random>
#include "../PokemonProject/include/pokedex.hpp"
#include "../PokemonProject/include/pokemon_party.hpp"
#include "../PokemonProject/include/pokemon_attack.hpp"
#include "BattleSystem.hpp"
#include <map>
#include <string>
#include <algorithm>

int main() {
    try {
        // Initialisation du Pokedex (Singleton)
        auto& dex = Pokedex::getInstance();
        std::cout << "Pokedex size: " << dex.size() << " Pokemon loaded." << std::endl;

        // Configuration de la fenêtre SFML
        sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Selector");
        window.setFramerateLimit(60);

        // Initialisation de la PokemonParty avec TOUS les Pokémon (898)
        PokemonParty party;
        for (int i = 1; i <= static_cast<int>(dex.size()); ++i) {
            if (auto p = dex.clone(i)) {
                party.add(p);
            } else {
                std::cerr << "Failed to clone Pokemon #" << i << std::endl;
            }
        }
        std::cout << "Party size: " << party.size() << " (all Pokemon loaded for grid)." << std::endl;

        // Sélection des Pokémon (jusqu'à 6)
        std::vector<Pokemon*> selectedPokemon;
        const int MAX_SELECTION = 6;

        // Création d'une équipe adverse aléatoire
        PokemonParty opponentParty;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, dex.size());
        for (int i = 0; i < 6; ++i) {
            if (auto p = dex.clone(dis(gen))) {
                opponentParty.add(p);
            }
        }

        // Cache des textures pour les sprites
        std::map<int, sf::Texture> textures;
        auto loadTexture = [&](int num) -> sf::Texture& {
            if (textures.find(num) == textures.end()) {
                sf::Texture tex;
                std::string path = "/mnt/c/Users/guesm/CLionProjects/PokemonProject/data/images/" + std::to_string(num) + ".png";
                if (!tex.loadFromFile(path)) {
                    std::cerr << "Failed to load texture: " << path << ", using fallback." << std::endl;
                    sf::Image img;
                    img.create(80, 80, sf::Color::Magenta);
                    tex.loadFromImage(img);
                }
                textures[num] = tex;
            }
            return textures[num];
        };

        // Chargement de la police
        sf::Font font;
        std::vector<std::string> fontPaths = {
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "data/arial.ttf"
        };
        bool fontLoaded = false;
        for (const auto& path : fontPaths) {
            if (font.loadFromFile(path)) {
                fontLoaded = true;
                break;
            }
        }

        // Chargement de la texture de fond
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("/mnt/c/Users/guesm/CLionProjects/PokemonProject/data/images/background.png")) {
            std::cerr << "Failed to load background texture, using fallback color." << std::endl;
        }

        // Texte de bienvenue et confirmation
        std::vector<sf::Text> glassTextLayers;
        sf::Text mainText;
        sf::Text selectionText;
        if (fontLoaded) {
            mainText.setFont(font);
            mainText.setCharacterSize(50);
            mainText.setFillColor(sf::Color(255, 255, 255, 200));
            mainText.setOutlineColor(sf::Color(100, 200, 255, 255));
            mainText.setOutlineThickness(3.0f);
            mainText.setStyle(sf::Text::Bold);

            selectionText.setFont(font);
            selectionText.setCharacterSize(30);
            selectionText.setFillColor(sf::Color::White);
            selectionText.setOutlineColor(sf::Color::Black);
            selectionText.setOutlineThickness(1.0f);
            selectionText.setPosition(20.f, 20.f);

            for (int i = 0; i < 4; ++i) {
                sf::Text layer("", font, 50);
                layer.setFillColor(sf::Color(150, 200, 255, 50));
                layer.setStyle(sf::Text::Bold);
                glassTextLayers.push_back(layer);
            }
        }

        // Variables d'animation et d'interface
        sf::Clock animationClock;
        float pulse = 1.0f;
        sf::Vector2i mousePos;
        sf::Clock welcomeClock;
        bool showWelcome = true;
        bool selectionComplete = false;
        bool showSelectedView = false;
        bool battleMode = false;
        bool showTooltip = false; // Added: Declare showTooltip
        BattleSystem* battleSystem = nullptr;

        // Défilement pour la grille PokemonParty
        float scrollOffset = 0.0f;
        const float scrollSpeed = 100.0f;
        const int COLS_PER_ROW = 8;
        const int POKEMON_SIZE = 80.f;
        const int FRAME_SIZE = 100.f;

        // Tooltip
        sf::Text tooltip;
        sf::Text playerPokemonText; // Label for player's Pokémon
        sf::Text opponentPokemonText; // Label for opponent's Pokémon
        if (fontLoaded) {
            tooltip.setFont(font);
            tooltip.setCharacterSize(20);
            tooltip.setFillColor(sf::Color::White);
            tooltip.setOutlineColor(sf::Color::Black);
            tooltip.setOutlineThickness(1.0f);

            // Initialize player and opponent Pokémon labels
            playerPokemonText.setFont(font);
            playerPokemonText.setCharacterSize(20);
            playerPokemonText.setFillColor(sf::Color::White);
            playerPokemonText.setOutlineColor(sf::Color::Black);
            playerPokemonText.setOutlineThickness(1.0f);
            playerPokemonText.setPosition(20.f, 320.f); // Near player's HP bar

            opponentPokemonText.setFont(font);
            opponentPokemonText.setCharacterSize(20);
            opponentPokemonText.setFillColor(sf::Color::White);
            opponentPokemonText.setOutlineColor(sf::Color::Black);
            opponentPokemonText.setOutlineThickness(1.0f);
            opponentPokemonText.setPosition(580.f, 70.f); // Near opponent's HP bar
        }

        // Battle background rectangle
        sf::RectangleShape battleBackground(sf::Vector2f(760.f, 300.f));
        battleBackground.setPosition(20.f, 20.f);
        battleBackground.setFillColor(sf::Color(0, 0, 0, 100)); // Semi-transparent black
        battleBackground.setOutlineColor(sf::Color::White);
        battleBackground.setOutlineThickness(2.f);

        // Drag and drop (optionnel, conservé)
        Pokemon* draggedPokemon = nullptr;
        sf::Vector2f dragOffset;
        bool isDragging = false;
        int dragIndex = -1;

        // Boucle principale
        while (window.isOpen()) {
            sf::Event event;
            mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::KeyPressed && showWelcome) {
                    if (event.key.code == sf::Keyboard::Space) showWelcome = false;
                } else if (!showWelcome && !selectionComplete && !showSelectedView && !battleMode) {
                    // Défilement avec la molette
                    if (event.type == sf::Event::MouseWheelScrolled) {
                        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                            scrollOffset -= event.mouseWheelScroll.delta * scrollSpeed;
                        }
                    }
                    // Défilement avec les touches
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Up) scrollOffset -= scrollSpeed;
                        if (event.key.code == sf::Keyboard::Down) scrollOffset += scrollSpeed;
                    }

                    // Limites pour défilement
                    int numRows = (party.size() + COLS_PER_ROW - 1) / COLS_PER_ROW;
                    float totalHeight = static_cast<float>(numRows * FRAME_SIZE);
                    scrollOffset = std::max(0.0f, std::min(scrollOffset, std::max(0.0f, totalHeight - 600.0f)));

                    // Clique pour sélectionner/désélectionner Pokémon
                    if (event.type == sf::Event::MouseButtonPressed) {
                        int col = static_cast<int>(mousePos.x / FRAME_SIZE);
                        int row = static_cast<int>((mousePos.y + scrollOffset) / FRAME_SIZE);
                        int adjustedIndex = row * COLS_PER_ROW + col;
                        if (adjustedIndex >= 0 && static_cast<size_t>(adjustedIndex) < party.size()) {
                            auto p = party.get(adjustedIndex);
                            if (p) {
                                auto it = std::find(selectedPokemon.begin(), selectedPokemon.end(), p);
                                if (it != selectedPokemon.end()) {
                                    selectedPokemon.erase(it);
                                    std::cout << "Deselected Pokemon #" << p->getNumero() << std::endl;
                                } else if (selectedPokemon.size() < MAX_SELECTION) {
                                    selectedPokemon.push_back(p);
                                    std::cout << "Selected Pokemon #" << p->getNumero() << std::endl;
                                    loadTexture(p->getNumero()); // Précharger la texture
                                } else {
                                    std::cout << "Maximum 6 Pokemon selected. Deselect one first." << std::endl;
                                }
                            }
                        }
                    }

                    // Confirmation avec Entrée si 6 sélectionnés
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && selectedPokemon.size() == MAX_SELECTION) {
                        selectionComplete = true;
                        showSelectedView = true;
                        std::cout << "Selection complete! Showing 6 chosen Pokemon." << std::endl;
                    }
                } else if (showSelectedView && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    showSelectedView = false;
                    battleMode = true;
                    // Précharger les textures de l'équipe adverse
                    for (int i = 0; i < 6; ++i) {
                        if (auto p = opponentParty.get(i)) {
                            loadTexture(p->getNumero());
                        }
                    }
                    battleSystem = new BattleSystem(selectedPokemon, opponentParty, font);
                    std::cout << "Battle mode activated with selected team." << std::endl;
                } else if (battleMode && event.type == sf::Event::MouseButtonPressed && battleSystem) {
                    // Gestion des clics sur les boutons d'attaque
                    for (size_t i = 0; i < battleSystem->getAttackButtons().size(); ++i) {
                        sf::FloatRect bounds = battleSystem->getAttackButtons()[i].getGlobalBounds();
                        if (bounds.contains(worldMousePos)) {
                            battleSystem->processTurn(0, i); // 0 = attaquer
                            break;
                        }
                    }
                }
            }

            // Gestion du tooltip
            if (!showWelcome && !selectionComplete && !showSelectedView && !battleMode && fontLoaded) {
                int col = static_cast<int>(mousePos.x / FRAME_SIZE);
                int row = static_cast<int>((mousePos.y + scrollOffset) / FRAME_SIZE);
                int adjustedIndex = row * COLS_PER_ROW + col;
                if (adjustedIndex >= 0 && static_cast<size_t>(adjustedIndex) < party.size()) {
                    auto p = party.get(adjustedIndex);
                    if (p) {
                        tooltip.setString("Pokemon #" + std::to_string(p->getNumero()) + " (cliquez pour toggle)");
                        sf::FloatRect tooltipRect = tooltip.getLocalBounds();
                        tooltip.setPosition(static_cast<float>(mousePos.x - tooltipRect.width / 2), static_cast<float>(mousePos.y - 40.f));
                        showTooltip = true;
                    } else {
                        showTooltip = false;
                    }
                } else {
                    showTooltip = false;
                }
            } else {
                showTooltip = false;
            }

            // Auto-dismiss du message de bienvenue
            if (showWelcome && welcomeClock.getElapsedTime().asSeconds() >= 3.0f) showWelcome = false;

            // Animation de pulsation
            pulse = 0.98f + 0.02f * std::sin(animationClock.getElapsedTime().asSeconds() * 2.0f);
            if (fontLoaded && showWelcome) {
                mainText.setScale(pulse, pulse);
                for (auto& layer : glassTextLayers) layer.setScale(pulse, pulse);
            }

            // Mise à jour du texte de sélection
            if (fontLoaded && !showWelcome && !showSelectedView && !battleMode) {
                selectionText.setString("Selectionnes: " + std::to_string(selectedPokemon.size()) + "/" + std::to_string(MAX_SELECTION) + " (Entrée pour confirmer)");
            }

            // Rendu
            window.clear();
            if (backgroundTexture.getSize().x > 0) {
                sf::Sprite backgroundSprite(backgroundTexture);
                backgroundSprite.setScale(static_cast<float>(800) / backgroundTexture.getSize().x, static_cast<float>(600) / backgroundTexture.getSize().y);
                window.draw(backgroundSprite);
            } else {
                window.clear(sf::Color(135, 206, 235));
            }

            if (showWelcome) {
                mainText.setString("Bienvenue ! Appuyez sur Espace pour voir la grille Pokemon.");
                sf::FloatRect textRect = mainText.getLocalBounds();
                mainText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                mainText.setPosition(400.0f, 300.0f);
                for (auto& layer : glassTextLayers) {
                    layer.setString("Bienvenue ! Appuyez sur Espace pour voir la grille Pokemon.");
                    layer.setPosition(402.0f, 302.0f);
                }
                if (fontLoaded) {
                    for (const auto& layer : glassTextLayers) window.draw(layer);
                    window.draw(mainText);
                }
            } else if (!selectionComplete && !showSelectedView && !battleMode) {
                int numRows = (party.size() + COLS_PER_ROW - 1) / COLS_PER_ROW;
                for (int row = 0; row < numRows; ++row) {
                    float rowY = static_cast<float>(row * FRAME_SIZE) - scrollOffset;
                    if (rowY >= -FRAME_SIZE && rowY <= 600.f) {
                        for (int col = 0; col < COLS_PER_ROW; ++col) {
                            int index = row * COLS_PER_ROW + col;
                            if (index >= static_cast<int>(party.size())) break;
                            auto p = party.get(index);
                            if (p) {
                                float xPos = static_cast<float>(col * FRAME_SIZE);
                                float yPos = rowY;
                                sf::RectangleShape frame(sf::Vector2f(FRAME_SIZE, FRAME_SIZE));
                                frame.setPosition(xPos, yPos);
                                frame.setFillColor(sf::Color::Transparent);
                                frame.setOutlineColor(sf::Color::White);
                                frame.setOutlineThickness(1.5f);
                                window.draw(frame);

                                sf::Sprite sprite(loadTexture(p->getNumero()));
                                sprite.setPosition(xPos + (FRAME_SIZE - POKEMON_SIZE) / 2.f, yPos + (FRAME_SIZE - POKEMON_SIZE) / 2.f);
                                sprite.setScale(1.f, 1.f);
                                window.draw(sprite);

                                auto it = std::find(selectedPokemon.begin(), selectedPokemon.end(), p);
                                if (it != selectedPokemon.end()) {
                                    sf::Text tick("✔", font, 28);
                                    tick.setFillColor(sf::Color::Green);
                                    tick.setOutlineColor(sf::Color::Black);
                                    tick.setOutlineThickness(1.0f);
                                    sf::FloatRect tickRect = tick.getLocalBounds();
                                    tick.setPosition(xPos + FRAME_SIZE - 25.f - tickRect.width / 2.f, yPos + 10.f - tickRect.height / 2.f);
                                    window.draw(tick);
                                }
                            }
                        }
                    }
                }

                if (fontLoaded) {
                    window.draw(selectionText);
                }

                if (showTooltip && fontLoaded) {
                    sf::FloatRect tooltipRect = tooltip.getLocalBounds();
                    sf::RectangleShape tooltipBg(sf::Vector2f(tooltipRect.width + 20, tooltipRect.height + 10));
                    tooltipBg.setPosition(tooltip.getPosition());
                    tooltipBg.setFillColor(sf::Color(0, 0, 0, 120));
                    tooltipBg.setOutlineColor(sf::Color::White);
                    tooltipBg.setOutlineThickness(1.f);
                    window.draw(tooltipBg);
                    window.draw(tooltip);
                }
            } else if (showSelectedView) {
                mainText.setString("Votre Equipe Selectionnee (6 Pokemon)");
                sf::FloatRect textRect = mainText.getLocalBounds();
                mainText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                mainText.setPosition(400.0f, 40.0f);
                window.draw(mainText);

                const int SELECTED_COLS = 3;
                const int SELECTED_ROWS = 2;
                const float SELECTED_SPACING = 20.f;
                const float SELECTED_FRAME_SIZE = 120.f;
                const float SELECTED_START_X = (800.f - (SELECTED_COLS * SELECTED_FRAME_SIZE + (SELECTED_COLS - 1) * SELECTED_SPACING)) / 2.f;
                const float SELECTED_START_Y = 120.f;
                for (size_t i = 0; i < selectedPokemon.size(); ++i) {
                    int row = i / SELECTED_COLS;
                    int col = i % SELECTED_COLS;
                    float xPos = SELECTED_START_X + col * (SELECTED_FRAME_SIZE + SELECTED_SPACING);
                    float yPos = SELECTED_START_Y + row * (SELECTED_FRAME_SIZE + SELECTED_SPACING);

                    sf::RectangleShape frame(sf::Vector2f(SELECTED_FRAME_SIZE, SELECTED_FRAME_SIZE));
                    frame.setPosition(xPos, yPos);
                    frame.setFillColor(sf::Color::Transparent);
                    frame.setOutlineColor(sf::Color::Green);
                    frame.setOutlineThickness(3.f);
                    window.draw(frame);

                    sf::Sprite sprite(loadTexture(selectedPokemon[i]->getNumero()));
                    float selectedPokemonSize = 96.f;
                    sprite.setPosition(xPos + (SELECTED_FRAME_SIZE - selectedPokemonSize) / 2.f, yPos + (SELECTED_FRAME_SIZE - selectedPokemonSize) / 2.f);
                    sprite.setScale(1.f, 1.f);
                    window.draw(sprite);

                    sf::Text numText("#" + std::to_string(selectedPokemon[i]->getNumero()), font, 18);
                    numText.setFillColor(sf::Color::White);
                    numText.setPosition(xPos + (SELECTED_FRAME_SIZE - numText.getLocalBounds().width) / 2.f, yPos + SELECTED_FRAME_SIZE + 10.f);
                    window.draw(numText);
                }

                sf::Text instrText("Appuyez sur Espace pour lancer le combat avec cette equipe.", font, 24);
                instrText.setFillColor(sf::Color::Yellow);
                sf::FloatRect instrRect = instrText.getLocalBounds();
                instrText.setOrigin(instrRect.left + instrRect.width / 2.0f, instrRect.top + instrRect.height / 2.0f);
                instrText.setPosition(400.0f, 520.0f);
                window.draw(instrText);
            } else if (battleMode && battleSystem) {
                // Draw battle background
                if (fontLoaded) {
                    window.draw(battleBackground);
                }

                // Render core battle elements (sprites, HP bars, attack buttons)
                battleSystem->render(window, textures);

                // Draw Pokémon labels (fallback as BattleSystem getters are unavailable)
                if (fontLoaded) {
                    playerPokemonText.setString("Votre Pokémon");
                    opponentPokemonText.setString("Pokémon adverse");
                    window.draw(playerPokemonText);
                    window.draw(opponentPokemonText);
                }

                // Draw battle end message if applicable
                if (battleSystem->isBattleOver()) {
                    sf::Text endText(battleSystem->getBattleMessage(), font, 30);
                    endText.setFillColor(sf::Color::Yellow);
                    sf::FloatRect endRect = endText.getLocalBounds();
                    endText.setOrigin(endRect.left + endRect.width / 2.0f, endRect.top + endRect.height / 2.0f);
                    endText.setPosition(400.0f, 300.0f);
                    window.draw(endText);
                }
            }

            window.display();
        }

        // Nettoyage
        delete battleSystem;
        Pokedex::destroyInstance();
    } catch (const std::exception& e) {
        std::cerr << "Erreur fatale : " << e.what() << std::endl;
        std::cin.get();
>>>>>>> 8c74afb (Sauvegarde avant pull)
        return 1;
    }
    return 0;
}