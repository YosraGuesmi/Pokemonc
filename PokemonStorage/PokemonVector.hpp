#ifndef POKEMON_VECTOR_HPP
#define POKEMON_VECTOR_HPP

#include "pokemon.hpp"
#include <vector>

class PokemonVector {
public:
    virtual ~PokemonVector() = default;
    virtual void add_pokemon(const Pokemon& pokemon) = 0;
    virtual const Pokemon* get_pokemon(int index) const = 0;
    virtual size_t size() const = 0;

protected:
    std::vector<Pokemon> pokemons_;
};

#endif // POKEMON_VECTOR_HPP