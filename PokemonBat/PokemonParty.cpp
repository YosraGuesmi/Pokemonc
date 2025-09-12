#include "PokemonParty.hpp"

void PokemonParty::add_pokemon(const Pokemon& pokemon) {
    pokemons_.push_back(pokemon);
}

const Pokemon* PokemonParty::get_pokemon(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < pokemons_.size()) {
        return &pokemons_[index];
    }
    return nullptr;
}

size_t PokemonParty::size() const {
    return pokemons_.size();
}

bool PokemonParty::remove_pokemon(int index) {
    if (index >= 0 && static_cast<size_t>(index) < pokemons_.size()) {
        pokemons_.erase(pokemons_.begin() + index);
        return true;
    }
    return false;
}