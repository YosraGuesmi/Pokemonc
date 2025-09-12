#include "PokemonVector.hpp"

void PokemonVector::add_pokemon(const Pokemon& pokemon) {
    pokemons_.push_back(pokemon);
}