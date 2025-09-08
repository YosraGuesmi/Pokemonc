#include "PokemonAttack.hpp"

PokemonAttack::PokemonAttack(const PokemonParty& party, const std::vector<int>& indices) {
    for (int index : indices) {
        if (pokemons_.size() < 6) {
            const Pokemon* pokemon = party.get_pokemon(index);
            if (pokemon) {
                pokemons_.push_back(*pokemon);
            }
        } else {
            break;
        }
    }
}

void PokemonAttack::add_pokemon(const Pokemon& pokemon) {
    if (pokemons_.size() < 6) {
        pokemons_.push_back(pokemon);
    }
}

const Pokemon* PokemonAttack::get_pokemon(int index) const {
    if (index >= 0 && static_cast<size_t>(index) < pokemons_.size()) {
        return &pokemons_[index];
    }
    return nullptr;
}

size_t PokemonAttack::size() const {
    return pokemons_.size();
}

void PokemonAttack::reintegrate_to_party(PokemonParty& party) {
    for (const auto& pokemon : pokemons_) {
        party.add_pokemon(pokemon);
    }
    pokemons_.clear();
}