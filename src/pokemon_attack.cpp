#include "pokemon_attack.hpp"
#include <algorithm>  // Already present

PokemonAttack* PokemonAttack::fromParty(const PokemonParty& party) {
    auto* attack = new PokemonAttack();
    size_t count = std::min(static_cast<size_t>(6), party.size());  // Cast pour matcher types
    for (size_t i = 0; i < count; ++i) {
        Pokemon* orig = party.get(static_cast<int>(i));
        if (orig) attack->add(new Pokemon(*orig));  // Deep copy
    }
    return attack;
}

void PokemonAttack::reintegrate(PokemonParty& party) {
    for (auto p : pokemons) {
        party.add(p);
    }
    pokemons.clear();
}

void PokemonAttack::add(Pokemon* p) {
    if (pokemons.size() < 6 && p) {
        pokemons.push_back(p);
    }
}

Pokemon* PokemonAttack::remove(int index) {
    if (index < 0 || static_cast<size_t>(index) >= pokemons.size()) return nullptr;
    Pokemon* p = pokemons[index];
    pokemons.erase(pokemons.begin() + index);
    return p;
}

void PokemonAttack::clear() {
    for (Pokemon* p : pokemons) {
        delete p;  // Delete dynamically allocated Pokemon objects
    }
    pokemons.clear();  // Clear the vector
}