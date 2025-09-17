#include "Pokedex.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

Pokedex* Pokedex::instance = nullptr;

Pokedex::Pokedex() {
    std::ifstream file("data/pokedex.csv");
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir pokedex.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;


        while (std::getline(ss, token, ',')) {

            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            tokens.push_back(token);
        }


        if (tokens.size() != 13) {
            std::cerr << "Ligne ignorée (mauvais nombre de colonnes) : " << line << std::endl;
            continue;
        }

        try {

            int num = std::stoi(tokens[0]);
            std::string nom = tokens[1];
            int evo = std::stoi(tokens[11]);
            int pvM = std::stoi(tokens[5]);
            int pvA = std::stoi(tokens[5]);
            int atk = std::stoi(tokens[6]);
            int def = std::stoi(tokens[7]);


            if (pvM <= 0 || pvA < 0 || pvA > pvM || atk < 0 || def < 0) {
                std::cerr << "Valeurs invalides pour " << nom << " : pvM=" << pvM << ", pvA=" << pvA << ", atk=" << atk << ", def=" << def << std::endl;
                continue;
            }


            Pokemon* p = new Pokemon(num, nom, evo, pvM, pvA, atk, def);
            pokemons.push_back(p);
            lookup[num] = p;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erreur de conversion pour ligne : " << line << " - " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Valeur hors limites pour ligne : " << line << " - " << e.what() << std::endl;
        }
    }

    file.close();

    if (pokemons.empty()) {
        std::cerr << "Attention : Pokedex vide, vérifiez pokedex.csv" << std::endl;
    } else {
        std::cout << "Pokedex chargé avec " << pokemons.size() << " Pokémon" << std::endl;
    }
}

Pokedex::~Pokedex() {
    for (Pokemon* p : pokemons) {
        delete p;
    }
    pokemons.clear();
    lookup.clear();
}

Pokedex& Pokedex::getInstance() {
    if (!instance) {
        instance = new Pokedex();
        if (instance->pokemons.empty()) {
            std::cerr << "Attention : Pokedex vide, vérifiez pokedex.csv" << std::endl;
        }
    }
    return *instance;
}

void Pokedex::destroyInstance() {
    delete instance;
    instance = nullptr;
}

Pokemon* Pokedex::clone(int num) const {
    auto it = lookup.find(num);
    if (it == lookup.end()) {
        std::cerr << "Pokémon #" << num << " non trouvé dans le Pokedex" << std::endl;
        return nullptr;
    }

    return new Pokemon(*(it->second));
}