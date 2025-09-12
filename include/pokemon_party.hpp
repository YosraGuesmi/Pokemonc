#pragma once
#include "pokemon_vector.hpp"

class PokemonParty : public PokemonVector {
public:
    void add(Pokemon* p) override { pokemons.push_back(p); }
    Pokemon* remove(int index) override;
};