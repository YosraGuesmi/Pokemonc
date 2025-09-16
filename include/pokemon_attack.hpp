#pragma once
#include "pokemon_vector.hpp"
#include "pokemon_party.hpp"

class PokemonAttack : public PokemonVector {
public:
    static PokemonAttack* fromParty(const PokemonParty& party);
    void reintegrate(PokemonParty& party);
    void add(Pokemon* p) override;
    Pokemon* remove(int index) override;
    void clear();  // New method to clear the vector and delete pointers
};