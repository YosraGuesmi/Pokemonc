#ifndef POKEMON_PARTY_HPP
#define POKEMON_PARTY_HPP

#include "../PokemonStorage/PokemonVector.hpp"
#include <cstddef>

class PokemonParty : public PokemonVector {
public:
    void add_pokemon(const Pokemon& pokemon) override;
    const Pokemon* get_pokemon(int index) const override;
    size_t size() const override;
    bool remove_pokemon(int index);
};

#endif // POKEMON_PARTY_HPP