#include "pokemon_party.hpp"

Pokemon* PokemonParty::remove(int index) {
    if (index < 0 || static_cast<size_t>(index) >= pokemons.size()) return nullptr;
    Pokemon* p = pokemons[index];
    pokemons.erase(pokemons.begin() + index);
    return p;
}