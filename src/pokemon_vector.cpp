#include "pokemon_vector.hpp"

PokemonVector::~PokemonVector() {
    for (auto p : pokemons) {
        delete p;
    }
}