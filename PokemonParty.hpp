#ifndef POKEMON_PARTY_HPP
#define POKEMON_PARTY_HPP

#include "PokemonVector.hpp"
#include <cstddef>

class PokemonParty : public PokemonVector {
public:
    const Pokemon* get_pokemon(int index) const override;
    size_t size() const override;
    bool remove_pokemon(int index);
};

#endif // POKEMON_PARTY_HPP