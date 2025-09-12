#ifndef POKEMON_ATTACK_HPP
#define POKEMON_ATTACK_HPP

#include "../PokemonStorage/PokemonVector.hpp"
#include "PokemonParty.hpp"
#include <vector>

class PokemonAttack : public PokemonVector {
public:
    PokemonAttack(const PokemonParty& party, const std::vector<int>& indices);
    void add_pokemon(const Pokemon& pokemon) override;
    const Pokemon* get_pokemon(int index) const override;
    size_t size() const override;
    void reintegrate_to_party(PokemonParty& party);
};

#endif // POKEMON_ATTACK_HPP