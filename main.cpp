#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "../PokemonProject/include/pokedex.hpp"
#include "../PokemonProject/include/pokemon_party.hpp"
#include "../PokemonProject/include/pokemon_attack.hpp"
#include <map>
#include <string>

int main() {
    try {
        // Initialize Pokedex and verify loading
        auto& dex = Pokedex::getInstance();
        std::cout << "Pokedex size: " << dex.size() << " Pokémon loaded." << std::endl;

        // Setup window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Pokemon Selector");
        window.setFramerateLimit(60);

        // Initialize party with Pokémon 1-12
        PokemonParty party;
        for (int i = 1; i <= 12; ++i) {
            if (auto p = dex.clone(i)) {
                party.add(p);
                std::cout << "Added Pokémon #" << i << " to party." << std::endl;
            } else {
                std::cerr << "Failed to clone Pokémon #" << i << std::endl;
            }
        }
        std::cout << "Party size: " << party.size() << std::endl;

        PokemonAttack* attack = new PokemonAttack();

        // Texture cache for sprites
        std::map<int, sf::Texture> textures;
        auto loadTexture = [&](int num) -> sf::Texture& {
            if (textures.find(num) == textures.end()) {
                sf::Texture tex;
                std::string path = "data/images/pokemon_" + std::to_string(num) + ".png";
                if (!tex.loadFromFile(path)) {
                    std::cerr << "Failed to load texture: " << path << ", using fallback." << std::endl;
                    sf::Image img;
                    img.create(64, 64, sf::Color::Green);
                    tex.loadFromImage(img);
                }
                textures[num] = tex;
            }
            return textures[num];
        };

        // Load font with multiple fallbacks
        sf::Font font;
        std::vector<std::string> fontPaths = {
            "data/arial.ttf",
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/msttcorefonts/Arial.ttf"
        };
        bool fontLoaded = false;
        for (const auto& path : fontPaths) {
            if (font.loadFromFile(path)) {
                std::cout << "Loaded font: " << path << std::endl;
                fontLoaded = true;
                break;
            }
        }
        if (!fontLoaded) {
            std::cerr << "Erreur: Aucune police trouvée. Le texte ne sera pas affiché." << std::endl;
        }

        // Setup welcome text
        std::vector<sf::Text> glassTextLayers;
        const std::string message = "you wanna play pokemon";
        const int fontSize = 50;

        sf::Text mainText;
        if (fontLoaded) {
            mainText.setFont(font);
            mainText.setString(message);
            mainText.setCharacterSize(fontSize);
            mainText.setFillColor(sf::Color(255, 255, 255, 200));
            mainText.setOutlineColor(sf::Color(100, 200, 255, 255));
            mainText.setOutlineThickness(3.0f);
            mainText.setStyle(sf::Text::Bold);

            for (int i = 0; i < 4; ++i) {
                sf::Text layer(message, font, fontSize);
                layer.setFillColor(sf::Color(150, 200, 255, 50));
                layer.setStyle(sf::Text::Bold);
                glassTextLayers.push_back(layer);
            }

            // Center text
            sf::FloatRect textRect = mainText.getLocalBounds();
            mainText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.height / 2.0f);
            mainText.setPosition(400.0f, 300.0f);

            glassTextLayers[0].setPosition(402.0f, 302.0f);
            glassTextLayers[1].setPosition(398.0f, 298.0f);
            glassTextLayers[2].setPosition(400.0f, 302.0f);
            glassTextLayers[3].setPosition(402.0f, 298.0f);
        }

        // Animation variables
        sf::Clock animationClock;
        float pulse = 1.0f;
        sf::Vector2i mousePos;
        int selectedPartyIndex = -1;
        int selectedAttackIndex = -1;
        sf::Clock welcomeClock;
        bool showWelcome = true;

        // Remove console input to avoid blocking
        // std::cout << "Appuyez sur Entrée pour continuer ou voir les erreurs..." << std::endl;
        // std::cin.get();

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed && !showWelcome) {
                    mousePos = sf::Mouse::getPosition(window);
                    if (mousePos.x < 400) {
                        selectedPartyIndex = static_cast<int>(mousePos.y / 80);
                        if (selectedPartyIndex >= 0 && static_cast<size_t>(selectedPartyIndex) < party.size()) {
                            auto p = party.remove(selectedPartyIndex);
                            if (p) {
                                attack->add(p);
                                std::cout << "Moved Pokémon to attack slot." << std::endl;
                            }
                        }
                    } else {
                        selectedAttackIndex = static_cast<int>(mousePos.y / 80);
                        if (selectedAttackIndex >= 0 && selectedAttackIndex < 6) {
                            auto p = attack->remove(selectedAttackIndex);
                            if (p) {
                                party.add(p);
                                std::cout << "Moved Pokémon back to party." << std::endl;
                            }
                        }
                    }
                } else if (event.type == sf::Event::KeyPressed && showWelcome) {
                    if (event.key.code == sf::Keyboard::Space) {
                        showWelcome = false;
                        std::cout << "Welcome screen dismissed." << std::endl;
                    }
                }
            }

            // Auto-dismiss welcome screen after 3 seconds
            if (showWelcome && welcomeClock.getElapsedTime().asSeconds() >= 3.0f) {
                showWelcome = false;
                std::cout << "Welcome screen auto-dismissed." << std::endl;
            }

            // Animation pulse
            pulse = 0.95f + 0.05f * std::sin(animationClock.getElapsedTime().asSeconds() * 2.0f);
            if (fontLoaded) {
                mainText.setScale(pulse, pulse);
                for (auto& layer : glassTextLayers) {
                    layer.setScale(pulse, pulse);
                }
            }

            window.clear(sf::Color::Black);

            if (showWelcome) {
                if (fontLoaded) {
                    for (const auto& layer : glassTextLayers) {
                        window.draw(layer);
                    }
                    window.draw(mainText);
                } else {
                    // Draw a fallback rectangle if font fails
                    sf::RectangleShape fallback(sf::Vector2f(200, 50));
                    fallback.setPosition(300, 275);
                    fallback.setFillColor(sf::Color::Red);
                    window.draw(fallback);
                }
            } else {
                // Draw party
                for (size_t i = 0; i < party.size(); ++i) {
                    auto p = party.get(static_cast<int>(i));
                    if (p) {
                        sf::Sprite sprite(loadTexture(p->getNumero()));
                        sprite.setPosition(50.f, 50.f + static_cast<float>(i * 80));
                        sprite.setScale(2.f, 2.f);
                        window.draw(sprite);
                    }
                }

                // Draw attack slots
                for (int i = 0; i < 6; ++i) {
                    sf::RectangleShape slot(sf::Vector2f(128.f, 64.f));
                    slot.setPosition(400.f, 50.f + static_cast<float>(i * 80));
                    slot.setFillColor(sf::Color::Transparent);
                    slot.setOutlineColor(sf::Color::White);
                    slot.setOutlineThickness(2.f);
                    window.draw(slot);
                    auto p = attack->get(i);
                    if (p) {
                        sf::Sprite sprite(loadTexture(p->getNumero()));
                        sprite.setPosition(410.f, 55.f + static_cast<float>(i * 80));
                        sprite.setScale(1.5f, 1.5f);
                        window.draw(sprite);
                    }
                }
            }

            window.display();
        }

        delete attack;
        Pokedex::destroyInstance();
    } catch (const std::exception& e) {
        std::cerr << "Erreur fatale : " << e.what() << std::endl;
        std::cout << "Appuyez sur Entrée pour quitter..." << std::endl;
        std::cin.get();
        return 1;
    }
    return 0;
}