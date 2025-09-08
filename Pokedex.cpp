#include "Pokedex.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

Pokedex::Pokedex() {
    load_from_csv("pokedex.csv");
}

Pokedex& Pokedex::get_instance() {
    static Pokedex instance;
    return instance;
}

void Pokedex::load_from_csv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open " + filename);
    }

    std::string line;
    std::getline(file, line);
    int line_number = 1;

    while (std::getline(file, line)) {
        line_number++;
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;


        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }


        if (tokens.size() != 13) {
            throw std::runtime_error("Invalid CSV line " + std::to_string(line_number) +
                                     ": expected 13 tokens, got " + std::to_string(tokens.size()) +
                                     " in line: " + line);
        }

        try {

            std::vector<int> numeric_indices = {0, 5, 6, 7};
            for (int idx : numeric_indices) {
                if (tokens[idx].empty()) {
                    throw std::runtime_error("Empty value at column " + std::to_string(idx + 1) +
                                             " in line " + std::to_string(line_number) + ": " + line);
                }
                for (char c : tokens[idx]) {
                    if (!std::isdigit(c) && c != '-') {
                        throw std::runtime_error("Invalid numeric value '" + tokens[idx] +
                                                 "' at column " + std::to_string(idx + 1) +
                                                 " in line " + std::to_string(line_number) + ": " + line);
                    }
                }
            }

            int id = std::stoi(tokens[0]);
            std::string name = tokens[1];
            int evolution = 0;
            int max_hp = std::stoi(tokens[5]);
            int attack = std::stoi(tokens[6]);
            int defense = std::stoi(tokens[7]);

            pokemons_.emplace_back(id, name, evolution, max_hp, attack, defense);
        } catch (const std::exception& e) {
            throw std::runtime_error("Error parsing CSV line " + std::to_string(line_number) +
                                     ": " + line + " (" + e.what() + ")");
        }
    }
    file.close();
}

void Pokedex::add_pokemon(const Pokemon& pokemon) {
    pokemons_.push_back(pokemon);
}

const Pokemon* Pokedex::get_pokemon(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < pokemons_.size()) {
        return &pokemons_[index];
    }
    return nullptr;
}

Pokemon* Pokedex::clone_pokemon(int id) {
    for (const auto& pokemon : pokemons_) {
        if (pokemon.get_id() == id) {
            return new Pokemon(pokemon.get_id(), pokemon.get_name(), pokemon.get_evolution(),
                              pokemon.get_max_hp(), pokemon.get_attack(), pokemon.get_defense());
        }
    }
    return nullptr;
}